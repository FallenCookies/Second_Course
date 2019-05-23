#pragma once

#include <iostream>
#include <memory>
#include "token.h"
#include "date.h"

using namespace std;
enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};
enum class LogicalOperation {
    And,
    Or
};
class Node{
public:
    Node(){}
virtual bool Evaluate(const Date& date, const string& event)=0;
};



class DateComparisonNode : public Node{
public:
    DateComparisonNode(Comparison cmp_,Date dt_);
    bool Evaluate(const Date& date, const string& event) override;

private:
    Comparison cmp;
    Date dt;
};
class EventComparisonNode  : public Node{
public:
    EventComparisonNode(Comparison cmp_,string event_);
    bool Evaluate(const Date& date, const string& event) override;
private:
    Comparison cmp;
    string  Event;
};
class LogicalOperationNode  : public Node{
public:
    LogicalOperationNode(const LogicalOperation& op,const shared_ptr<Node>& left_,const shared_ptr<Node>& right_);

    bool Evaluate(const Date& date, const string& event) override;

private:
    LogicalOperation operation;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};
class EmptyNode : public Node{
public:
    EmptyNode(){
    }
    bool Evaluate(const Date& date, const string& event)  override;
};