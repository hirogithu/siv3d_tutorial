
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

double euclid_distance(Vec2 a, Vec2 b)
{//2点の座標のユークリッド距離を返す
	return Math::Sqrt(Math::Square(a.x - b.x) + Math::Square(a.y - b.y));
}

void tutorial_01()
{// How to Print
	while (System::Update())
	{
		ClearPrint();

		Print << Cursor::Pos();

		Print << U"X: "<< Cursor::Pos().x;

		Print << U"Y: "<< Cursor::Pos().y;
	}
}

void tutorial_02()
{// How to draw shapes
	while (System::Update())
	{
		const double hue = Scene::Time() * 60.0;

		Scene::SetBackground(HSV(hue, 0.6, 1.0));

		Circle(100, 200, 40).draw();

		Circle(200, 200, 40).draw(Palette::Green);

		Circle(300, 200, 40).draw(Palette::Red);

		// 図形は draw() した順番に描画されます。
		Circle(Cursor::Pos(), 80).draw(ColorF(0.5, 0.3, 0.1, 0.7));

		Circle(400, 200, 40).draw(Palette::Orange);
	}
	
}

void tutorial_03()
{//How to make animation
	Scene::SetBackground(ColorF(0.25));

	Transition transition(2.0s, 0.3s);

	while (System::Update())
	{
		transition.update(MouseL.pressed());

		const double t = transition.value();

		Circle(Scene::Center(), 200).drawPie(0_deg, 360_deg * t);
	}
	
}

void tutorial_04()
{//2d-intersection

	Window::SetTitle(U"Match the cat!");

	Scene::SetBackground(ColorF(0.7, 0.9, 0.8));

	const Texture texture(Emoji(U"🐈"));

	constexpr Vec2 begin(50, 300);	 // set begin of cat
	constexpr Vec2 end(400, 300);	 // set end of cat
	constexpr Vec2 center(400, 150); // set title

	Vec2 pos = begin;

	Stopwatch stopwatch(true);

	double sin_t = 0.0;

	const Font font(60, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"arial.ttf");

	double slider_value = 3.0;

	while (System::Update())
	{
		font(U"Match the CAT!").drawAt(center.movedBy(4, 4), ColorF(0.0, 0.5));
		font(U"Match the CAT!").drawAt(center);

		// center cat
		texture.drawAt(Scene::Center());

		// select speed
		SimpleGUI::Slider(U"Speed {:.2f}"_fmt(slider_value), slider_value, 0.1, 100, end.movedBy(-80, 190), 140, 200);

		if (stopwatch.isPaused())
		{
			if (SimpleGUI::Button(U"Restart", end.movedBy(-50, 150)))
			{
				stopwatch.resume();
				ClearPrint();
				Scene::SetBackground(ColorF(0.7, 0.9, 0.8));			}
		}
		else
		{
			if (SimpleGUI::Button(U"Stop", end.movedBy(-50, 150)))
			{
				stopwatch.pause();

				Print << U"sin_t: " << sin_t;

				double score = 1 - euclid_distance(pos, end) / euclid_distance(begin, end);

				Print << U"score: " << score;

				if (score == 1.0)
				{
					font(U"Brilliant!").drawAt(end.movedBy(100, -20));
					Scene::SetBackground(Palette::Red);
				}
				else if (score <1.0 && score >= 0.70)
				{
					font(U"Good!").drawAt(end.movedBy(100, -20));
					Scene::SetBackground(Palette::Violet);
				}
				
			}
		}
		// move the cat
		if (stopwatch.isRunning())
		{
			const double t = stopwatch.sF();
			sin_t = (1. + sin(slider_value * t)) / 2.;
			pos = begin.lerp(end, sin_t);
		}
		texture.drawAt(pos);

	}
}

void tutorial_00()
{//To do
	while (System::Update())
	{
		/* code */
	}
}

void Main()
{
	tutorial_04();
}
