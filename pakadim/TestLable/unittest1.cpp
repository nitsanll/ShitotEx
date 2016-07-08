#include "CppUnitTest.h"
#include "label.h"
#include "GraphicsMock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLabel
{		
	TEST_CLASS(TestLabel)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			GraphicsMock g;
			Label label(5, "label");
			label.setPosition({ 0,0 });
			label.setForeground(Color::Black);
			label.setBackground(Color::Red);
			label.draw(g, 0, 0, 0);
			
			Assert::IsFalse(label.canGetFocus());
			Assert::AreEqual(label.innerTab() , false);
			Assert::AreEqual(label.getCol(), short(0));
			Assert::AreEqual(label.getLine(), short(0));
			Assert::AreEqual(label.getWidth(), 5);
			Assert::AreEqual(label.getHeight(), 1);
			Assert::IsTrue(label.getVisibility());
			g.clearAt(0, 0, 5);
			Assert::IsTrue(g.isClear());
			
		}
	};
}