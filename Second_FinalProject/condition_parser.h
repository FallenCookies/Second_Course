#pragma once
#include "test_runner.h"
#include "node.h"
#include "token.h"
#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);


void TestParseCondition();
