#include "test_runner.h"
#include "database.h"
#include "condition_parser.h"
#include <sstream>

using Entry=pair<Date,string>;
ostream& operator<<(ostream& os, const pair<Date,string>& p){
	os<<p.first<<" "<<p.second;
	return os;
}
int DoRemove (Database& db, const string& str) {
	istringstream is (str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date &date, const string &event) {
		return condition->Evaluate(date, event);
	};
	return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
	istringstream is (str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date &date, const string &event) {
		return condition->Evaluate(date, event);
	};
	const auto entries = db.FindIf(predicate);
	ostringstream os;
	for (const auto& entry : entries) {
		os << entry << endl;
	}
	os << entries.size();
	return os.str();
}

void TestDbAdd() {
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 7}, "xmas");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
	}
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 1}, "holiday");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
	}
	{
		Database db;
		db.Add({2017, 1, 7}, "xmas");
		db.Add({2017, 1, 1}, "new year");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
	}
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 1}, "xmas");
		db.Add({2017, 1, 1}, "new year");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
	}
}

void TestDbFind() {
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 7}, "xmas");
		AssertEqual("2017-01-01 new year\n1", DoFind(db, "date == 2017-01-01"), "simple find by date");
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, "date < 2017-01-31"), "multiple find by date");
		AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(event != "xmas")"), "multiple find by holiday");
	}
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 1}, "new year2");
		db.Add({2017, 1, 7}, "xmas");
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, R"(date == 2017-01-07 OR event == "new year")"),
					"complex find or");
		AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(date == 2017-01-01 AND event == "new year")"),
					"complex find and");
		AssertEqual("0", DoFind(db, R"(date == 2017-01-09 AND event == "new year")"),
					"complex find and, nothing");
	}
}

void TestDbLast(){
	Database db;
	db.Add({2017, 1, 1}, "new year");
	db.Add({2017, 1, 7}, "xmas");
	{
		try {
			db.Last({2016, 12, 31});
			Assert(false, "last, found no entries");
		} catch (...){
			Assert(true, "last, found no entries");

		}
	}
	{
		ostringstream os;
		os << db.Last({2017, 1, 2});
		AssertEqual("2017-01-01 new year", os.str(), "greater than date");
	}
	{
		ostringstream os;
		os << db.Last({2017, 1, 1});
		AssertEqual("2017-01-01 new year", os.str(), "eq to date");
	}
	{
		ostringstream os;
		os << db.Last({2017, 1, 10});
		AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
	}
}

void TestDbRemoveIf () {
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 7}, "xmas");
		AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
		AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
	}
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 7}, "xmas");
		AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
	}
	{
		Database db;
		db.Add({2017, 1, 1}, "new year");
		db.Add({2017, 1, 7}, "xmas");
		db.Add({2017, 1, 7}, "new year");
		AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
	}
}
void TestDateComparison(){

			Assert(Date{2017, 11, 18} == Date{2017, 11, 18}, "Compare date 1");
			Assert(Date{2017, 11, 18} != Date{2017, 11, 19}, "Compare date 2");

			Assert(Date{2017, 11, 18} < Date{2017, 11, 19}, "Compare date 3");
			Assert(Date{2017, 10, 18} < Date{2017, 11, 19}, "Compare date 4");
			Assert(Date{2016, 11, 18} < Date{2017, 11, 19}, "Compare date 5");
			Assert(Date{2017, 11, 20} > Date{2017, 11, 19}, "Compare date 6");
			Assert(Date{2017, 12, 18} > Date{2017, 11, 19}, "Compare date 7");
			Assert(Date{2018, 11, 18} > Date{2017, 11, 19}, "Compare date 8");

			Assert(Date{2017, 11, 18} >= Date{2017, 11, 18}, "Compare date 9");
			Assert(Date{2017, 11, 18} <= Date{2017, 11, 18}, "Compare date 10");

			Assert(Date{2017, 11, 18} <= Date{2017, 11, 19}, "Compare date 11");
			Assert(Date{2017, 10, 18} <= Date{2017, 11, 19}, "Compare date 12");
			Assert(Date{2016, 11, 18} <= Date{2017, 11, 19}, "Compare date 13");
			Assert(Date{2017, 11, 20} >= Date{2017, 11, 19}, "Compare date 14");
			Assert(Date{2017, 12, 18} >= Date{2017, 11, 19}, "Compare date 15");
			Assert(Date{2018, 11, 18} >= Date{2017, 11, 19}, "Compare date 16");

	}
void TestParseDate() {
	{
		istringstream is("2017-11-18");
		Date date = ParseDate(is);
		AssertEqual(date, Date{2017, 11, 18}, "Parse date 1");
		AssertEqual(date.year, 2017, "Parse date 2");
		AssertEqual(date.month, 11, "Parse date 3");
		AssertEqual(date.day, 18, "Parse date 4");
		Assert(date != Date{2017, 1, 1}, "Parse date 5");
	}
	{
		istringstream is("     2017-1-14");
		Date date = ParseDate(is);
		AssertEqual(date, Date{2017, 01, 14}, "Parse date 6");
		ostringstream os;
		os << date;
		AssertEqual(os.str(), "2017-01-14", "Parse date 7");
	}
	{
		istringstream is("0-1-1");
		Date date = ParseDate(is);
		AssertEqual(date, Date{0, 1, 1}, "Parse date 8");
		ostringstream os;
		os << date;
		AssertEqual(os.str(), "0000-01-01", "Parse date 9");
	}
	{
		istringstream is("9999-12-31");
		Date date = ParseDate(is);
		AssertEqual(date, Date{9999, 12, 31}, "Parse date 10");
		ostringstream os;
		os << date;
		AssertEqual(os.str(), "9999-12-31", "Parse date 11");
	}

}
void AssertDbPrintOutput(const Database& db, const string& hint, const vector<string> expected) {
	stringstream str;
	db.Print(str);

	string str_print;

	size_t i = 0;
	while(getline(str, str_print)) {
		stringstream msg;
		msg << hint << ' ' << i;
		AssertEqual(str_print , expected[i], msg.str());
		i++;
	}
	stringstream eof_msg;
	eof_msg << hint << " eof";
	Assert(str.eof(), eof_msg.str());
}
void TestDatabasePrint() {
	{
		Database db;
		db.Add({ 2017,1,1 }, "Holiday");
		db.Add({ 2017,1,1 }, "Holiday");
		db.Add({ 2017,1,1 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,1,1 }, "New Year");
		db.Add({ 2017,1,1 }, "New Year");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,3,8 }, "Holiday");
		db.Add({ 2017,1,1 }, "Holiday");
		db.Add({ 2017,1,1 }, "Holiday");
		db.Add({ 2017,1,1 }, "Holiday");

		AssertDbPrintOutput(db, "print value", {
				"2017-01-01 Holiday",
				"2017-01-01 New Year",
				"2017-03-08 Holiday",
				""
		});
	}
	{
		Database db;
		stringstream str;
		db.Print(str);

		AssertDbPrintOutput(db, "print value", {
				""
		});
	}
}
void TestDatabaseDel() {
	{
		Database db;

		db.Add({ 2017, 6, 1 }, "1st of June");
		db.Add({ 2017, 6, 2 }, "2nd of June");
		db.Add({ 2017, 6, 3 }, "3rd of June");
		db.Add({ 2017, 6, 4 }, "4th of June");
		db.Add({ 2017, 6, 5 }, "5th of June");
		db.Add({ 2017, 7, 8 }, "8th of July");
		db.Add({ 2017, 7, 8 }, "Someone's birthday");
		db.Add({ 2017, 7, 8 }, "Buy groceries");
		db.Add({ 2017, 7, 9 }, "9th of July");
		db.Add({ 2017, 7, 10 }, "10th of July");
		db.Add({ 2017, 7, 11 }, "11th of July");
		db.Add({ 2017, 7, 12 }, "12th of July");
		db.Add({ 2017, 7, 13 }, "13th of July");
		db.Add({ 2017, 7, 14 }, "14th of July");

		auto predicate = [](const Date& date, const string& event) {
			return date == Date { 2017, 7, 8 };
		};

		int removed = db.RemoveIf(predicate);
		AssertEqual(removed, 3, "delete case 1");

		AssertDbPrintOutput(db, "delete case 1 print", {
				"2017-06-01 1st of June",
				"2017-06-02 2nd of June",
				"2017-06-03 3rd of June",
				"2017-06-04 4th of June",
				"2017-06-05 5th of June",
				"2017-07-09 9th of July",
				"2017-07-10 10th of July",
				"2017-07-11 11th of July",
				"2017-07-12 12th of July",
				"2017-07-13 13th of July",
				"2017-07-14 14th of July",
				""
		});
	}
	{
		Database db;

		db.Add({ 2017, 6, 1 }, "1st of June");
		db.Add({ 2017, 6, 2 }, "2nd of June");
		db.Add({ 2017, 6, 3 }, "3rd of June");
		db.Add({ 2017, 6, 4 }, "4th of June");
		db.Add({ 2017, 6, 5 }, "5th of June");
		db.Add({ 2017, 7, 8 }, "8th of July");
		db.Add({ 2017, 7, 8 }, "Someone's birthday");
		db.Add({ 2017, 7, 9 }, "9th of July");
		db.Add({ 2017, 7, 10 }, "10th of July");
		db.Add({ 2017, 7, 11 }, "11th of July");
		db.Add({ 2017, 7, 12 }, "12th of July");
		db.Add({ 2017, 7, 13 }, "13th of July");
		db.Add({ 2017, 7, 14 }, "14th of July");

		auto predicate = [](const Date& date, const string& event) {
			return date >= Date { 2017, 7, 1 };
		};

		int removed = db.RemoveIf(predicate);
		AssertEqual(removed, 8, "delete case 2");

		AssertDbPrintOutput(db, "delete case 2 print", {
				"2017-06-01 1st of June",
				"2017-06-02 2nd of June",
				"2017-06-03 3rd of June",
				"2017-06-04 4th of June",
				"2017-06-05 5th of June",
				""
		});
	}
	{
		Database db;

		db.Add({ 2017, 6, 1 }, "work");
		db.Add({ 2017, 6, 1 }, "sleep");
		db.Add({ 2017, 6, 2 }, "work");
		db.Add({ 2017, 6, 2 }, "sleep");
		db.Add({ 2017, 6, 3 }, "work");
		db.Add({ 2017, 6, 3 }, "sleep");
		db.Add({ 2017, 6, 4 }, "work");
		db.Add({ 2017, 6, 4 }, "sleep");
		db.Add({ 2017, 6, 5 }, "play computer games");
		db.Add({ 2017, 6, 5 }, "sleep");
		db.Add({ 2017, 6, 6 }, "visit parents");
		db.Add({ 2017, 6, 6 }, "sleep");
		db.Add({ 2017, 6, 7 }, "work");
		db.Add({ 2017, 6, 7 }, "sleep");
		db.Add({ 2017, 6, 8 }, "sleep");

		auto predicate = [](const Date& date, const string& event) {
			return event == "work";
		};

		int removed = db.RemoveIf(predicate);
		AssertEqual(removed, 5, "delete case 3");

		AssertDbPrintOutput(db, "delete case 3 print", {
				"2017-06-01 sleep",
				"2017-06-02 sleep",
				"2017-06-03 sleep",
				"2017-06-04 sleep",
				"2017-06-05 play computer games",
				"2017-06-05 sleep",
				"2017-06-06 visit parents",
				"2017-06-06 sleep",
				"2017-06-07 sleep",
				"2017-06-08 sleep",
				""
		});
	}
}
void TestDatabaseLast() {
	{
		Database db;

		db.Add({ 2017, 11, 21 }, "Tuesday");
		db.Add({ 2017, 11, 20 }, "Monday");
		db.Add({ 2017, 11, 21 }, "Weekly meeting");
		db.Last({ 2017, 11, 21 });
		AssertEqual(db.Last({ 2017, 11, 20 }), Entry{{ 2017, 11, 20 }, "Monday"}, "last case 1");
		AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 2");
		try {
			db.Last({ 2000, 1, 1 });
			throw domain_error("last case 3: Shouldn't get here");
		} catch(const invalid_argument& e) {

		}

		auto predicate = [](const Date& date, const string& event) {
			return event == "Weekly meeting";
		};

		db.RemoveIf(predicate);
		AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Tuesday"}, "last case 4");
		AssertEqual(db.Last({ 9999, 12, 31 }), Entry{{ 2017, 11, 21 }, "Tuesday"}, "last case 5");

		db.Add({ 2017, 11, 21 }, "Weekly meeting");
		AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 6");
		AssertEqual(db.Last({ 9999, 12, 31 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 7");
	}
}
void TestDatabaseFind() {
	{
		Database db;

		db.Add({ 2017, 6, 1 }, "work");
		db.Add({ 2017, 6, 1 }, "sleep");
		db.Add({ 2017, 6, 2 }, "work");
		db.Add({ 2017, 6, 2 }, "sleep");
		db.Add({ 2017, 6, 3 }, "work");
		db.Add({ 2017, 6, 3 }, "sleep");
		db.Add({ 2017, 6, 4 }, "work");
		db.Add({ 2017, 6, 4 }, "sleep");
		db.Add({ 2017, 6, 5 }, "play computer games");
		db.Add({ 2017, 6, 5 }, "sleep");
		db.Add({ 2017, 6, 6 }, "visit parents");
		db.Add({ 2017, 6, 6 }, "sleep");
		db.Add({ 2017, 6, 7 }, "work");
		db.Add({ 2017, 6, 7 }, "sleep");
		db.Add({ 2017, 6, 8 }, "sleep");

		auto predicate1 = [](const Date& date, const string& event) {
			return event == "work";
		};

		vector<Entry> found1 = db.FindIf(predicate1);
		AssertEqual(found1, vector<Entry>{
				{{ 2017, 6, 1 }, "work"},
				{{ 2017, 6, 2 }, "work"},
				{{ 2017, 6, 3 }, "work"},
				{{ 2017, 6, 4 }, "work"},
				{{ 2017, 6, 7 }, "work"}
		}, "find case 1");
	}
	{
		Database db;

		db.Add({ 2017, 6, 1 }, "work");
		db.Add({ 2017, 6, 1 }, "sleep");
		db.Add({ 2017, 6, 2 }, "work");
		db.Add({ 2017, 6, 2 }, "sleep");
		db.Add({ 2017, 6, 3 }, "work");
		db.Add({ 2017, 6, 3 }, "sleep");
		db.Add({ 2017, 6, 4 }, "work");
		db.Add({ 2017, 6, 4 }, "sleep");
		db.Add({ 2017, 6, 5 }, "play computer games");
		db.Add({ 2017, 6, 5 }, "sleep");
		db.Add({ 2017, 6, 6 }, "visit parents");
		db.Add({ 2017, 6, 6 }, "sleep");
		db.Add({ 2017, 6, 7 }, "work");
		db.Add({ 2017, 6, 7 }, "sleep");
		db.Add({ 2017, 6, 8 }, "sleep");

		auto predicate1 = [](const Date& date, const string& event) {
			return event != "work";
		};

		vector<Entry> found1 = db.FindIf(predicate1);
		AssertEqual(found1, vector<Entry>{
				{{ 2017, 6, 1 }, "sleep"},
				{{ 2017, 6, 2 }, "sleep"},
				{{ 2017, 6, 3 }, "sleep"},
				{{ 2017, 6, 4 }, "sleep"},
				{{ 2017, 6, 5 }, "play computer games"},
				{{ 2017, 6, 5 }, "sleep"},
				{{ 2017, 6, 6 }, "visit parents"},
				{{ 2017, 6, 6 }, "sleep"},
				{{ 2017, 6, 7 }, "sleep"},
				{{ 2017, 6, 8 }, "sleep"}
		}, "find case 2");
	}}