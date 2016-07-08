#include "iControl.h"
#include "TextBox.h"
#include "CheckList.h"
#include "RadioList.h"
#include "Panel.h"
#include "label.h"
#include "combobox.h"
#include "EventEngine.h"
#include "numericBox.h"
#include "Message.h"
#include <iostream>

using namespace std;
int main()
{
	Panel panel(30, 30);
	Label label(4, "hi!");
	label.setForeground(Color::Red);
	label.setBackground(Color::White);
	label.setBorder(BorderType::Single);
	TextBox text(5);
	text.SetText("t2");
	text.setForeground(Color::Blue);
	text.setBackground(Color::White);
	text.setBorder(BorderType::Single);
	Button b(1);
	b.SetText("+");
	b.setForeground(Color::Red);
	b.setBorder(BorderType::Single);
	CheckList check(4, 4, { "134", "34", "111", "123" });
	check.setBorder(BorderType::Single);
	RadioList radio(2, 5, { "123", "1234" });
	radio.setBorder(BorderType::Single);
	NumericBox num(4, 1, 3);
	num.setBorder(BorderType::Single);
	Messagebox box(5, 10);
	box.setBorder(BorderType::Single);
	Combo combo(5, { "1990", "1991", "1992" });
	combo.setBorder(BorderType::Single);
	panel.AddiControl(label, 2, 2);
	panel.AddiControl(text, 2, 6);
	panel.AddiControl(b, 2, 10);
	panel.AddiControl(check, 2, 14);
	panel.AddiControl(radio, 2, 21);
	panel.AddiControl(num, 2, 25);
	panel.AddiControl(box, 2, 28);
	panel.AddiControl(combo, 2, 36);
	iControl::setFocus(text);
	EventEngine engine;
	engine.run(panel);
	return 0;
}