#ifndef SIMPLEBORDERFACTORY_H_
#define SIMPLEBORDERFACTORY_H_
#include "BorderDrawer.h"
#include "NullBorderDrawer.h"
#include "SingleBorderDrawer.h"
#include "DoubleBorderDrawer.h"

class SimpleBorderFactory {
public:
	const BorderDrawer& getNull() { return _null; }
	const BorderDrawer& getSingle() { return _single; }
	const BorderDrawer& getDouble() { return _double; }
	static SimpleBorderFactory& instance() { static SimpleBorderFactory instance; return instance; }
	SimpleBorderFactory(SimpleBorderFactory const&) = delete;
	void operator=(SimpleBorderFactory const&) = delete;
	const BorderDrawer& getBorderDrawer(BorderType type) //which type of border was choosen
	{
		switch (type)
		{
		case BorderType::Null: return _null;
		case BorderType::Single: return _single;
		case BorderType::Double: return _double;
		}
	}
private:
	SimpleBorderFactory() {} //singleton
	NullBorderDrawer _null;
	SingleBorderDrawer _single;
	DoubleBorderDrawer _double;
};
#endif