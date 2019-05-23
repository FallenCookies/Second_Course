//
// Created by vlad on 22.02.2019.
//

#include "date.h"
#include "node.h"

bool Node::Evaluate(const Date &date, const string &event) {
    return false;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &op, const
shared_ptr<Node> &left_, const shared_ptr<Node>& right_)
        :operation(op),left(left_),right(right_)  {
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) {
    if (operation==LogicalOperation::And){
        return left->Evaluate(date,event) && right->Evaluate(date,event);
    }
    if (operation==LogicalOperation::Or){
        return left->Evaluate(date,event) || right->Evaluate(date,event);
    }
    cout <<"Logical operator type error ";
    return false;
}

bool EmptyNode::Evaluate(const Date &date, const string &event) {
    return true;
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) {
    if (cmp==Comparison ::Less){
        return event<Event;
    }
    if (cmp==Comparison::Equal){
        return event==Event;
    }
    if (cmp==Comparison::Greater){
        return event>Event;
    }
    if (cmp==Comparison::GreaterOrEqual){
        return event>Event || event==Event;
    }
    if (cmp==Comparison::LessOrEqual){
        return event<Event || event==Event;
    }
    if (cmp==Comparison::NotEqual)
        return !(event == Event);
    cout <<"Comparsion type error ";
    return false;
}

EventComparisonNode::EventComparisonNode(Comparison cmp_, string event_) :cmp(cmp_),Event(event_){

}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    if (cmp==Comparison ::Less){
        return date<dt;
    }
    if (cmp==Comparison::Equal){
        return date==dt;
    }
    if (cmp==Comparison::Greater){
        return date>dt;
    }
    if (cmp==Comparison::GreaterOrEqual){
        return date>dt || date==dt;
    }
    if (cmp==Comparison::LessOrEqual){
        return date<dt || date==dt;
    }
    if (cmp==Comparison::NotEqual)
        return !(date == dt);


    cout <<"Comparsion type error ";
    return false;
}

DateComparisonNode::DateComparisonNode(Comparison cmp_, Date dt_) :cmp(cmp_),dt(dt_){


}
