#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <hexagon.hpp>

TEST_CASE("Test first","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    auto pos = hex.get_position();
    REQUIRE(pos.first == 0);
    REQUIRE(pos.second == 0);
}

TEST_CASE("Test multiple, emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    auto pos = hex.get_position();
    REQUIRE(pos.first == 0);
    REQUIRE(pos.second == 0);

    hexagon* a,*b,*c,*d,*e,*f;
    REQUIRE((a = hex.emplace(0)) != nullptr);
    REQUIRE((b = hex.emplace(1)) != nullptr);
    REQUIRE((c = hex.emplace(2)) != nullptr);
    REQUIRE((d = hex.emplace(3)) != nullptr);
    REQUIRE((e = hex.emplace(4)) != nullptr);
    REQUIRE((hex.emplace(-1)) == nullptr);
    REQUIRE((hex.emplace(5)) == nullptr);

    REQUIRE(hex.emplace(100) == nullptr);

    REQUIRE(hex.emplace(200) == nullptr);


    auto a_pos = a->get_position();
    auto b_pos = b->get_position();
    auto c_pos = c->get_position();
    auto d_pos = d->get_position();
    auto e_pos = e->get_position();

    REQUIRE(a_pos.first == 0);
    REQUIRE(a_pos.second == 1);
    REQUIRE(b_pos.first == 1);
    REQUIRE(b_pos.second == 1);
    REQUIRE(c_pos.first == 1);
    REQUIRE(c_pos.second == 0);
    REQUIRE(d_pos.first == 0);
    REQUIRE(d_pos.second == -1);
    REQUIRE(e_pos.first == -1);
    REQUIRE(e_pos.second == -1);

}

TEST_CASE("Test multiple,2nd lvl basic emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*b1,*c2,*d2,*e2,*f2,*g2,*h1;
    REQUIRE((b1 = hex.emplace(2)) != nullptr);
    REQUIRE((a1 = hex.emplace(0)) != nullptr);
    REQUIRE((c2 = b1->emplace(0)) != nullptr);
    REQUIRE((d2 = b1->emplace(1)) != nullptr);
    REQUIRE((e2 = b1->emplace(2)) != nullptr);
    REQUIRE((f2 = b1->emplace(3)) != nullptr);
    REQUIRE((g2 = b1->emplace(4)) != nullptr);
    REQUIRE((h1 = hex.emplace(4)) != nullptr);

    auto c_pos = c2->get_position();
    auto d_pos = d2->get_position();
    auto e_pos = e2->get_position();
    auto f_pos = f2->get_position();
    auto g_pos = g2->get_position();


    REQUIRE(c_pos.first == 1);
    REQUIRE(c_pos.second == 1);
    REQUIRE(d_pos.first == 2);
    REQUIRE(d_pos.second == 1);
    REQUIRE(e_pos.first == 2);
    REQUIRE(e_pos.second == 0);
    REQUIRE(f_pos.first == 1);
    REQUIRE(f_pos.second == -1);
    REQUIRE(g_pos.first == 0);
    REQUIRE(g_pos.second == -1);
}

TEST_CASE("Test multiple, 2nd lvl overlapping refuse","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*b1,*c2,*d2,*e2,*f2,*g2,*h1,*i1;
    REQUIRE(hex.emplace(0) != nullptr);
    REQUIRE((b1 = hex.emplace(2)) != nullptr);
    REQUIRE(b1->emplace(0) != nullptr);
    REQUIRE(b1->emplace(1) != nullptr);
    REQUIRE(b1->emplace(2) != nullptr);
    REQUIRE(b1->emplace(3) != nullptr);
    REQUIRE(b1->emplace(4) != nullptr);
    REQUIRE(hex.emplace(4) != nullptr);
    REQUIRE(hex.emplace(1) == nullptr);
    REQUIRE(hex.emplace(3) == nullptr);
}

TEST_CASE("Test multiple,2nd lvl tilted 0 emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*b1,*c2,*d2,*e2,*f2,*g2,*h1;
    REQUIRE((a1 = hex.emplace(0)) != nullptr);
    REQUIRE((c2 = a1->emplace(0)) != nullptr);
    REQUIRE((d2 = a1->emplace(1)) != nullptr);
    REQUIRE((e2 = a1->emplace(2)) != nullptr);
    REQUIRE((f2 = a1->emplace(3)) != nullptr);
    REQUIRE((g2 = a1->emplace(4)) != nullptr);

    auto c_pos = c2->get_position();
    auto d_pos = d2->get_position();
    auto e_pos = e2->get_position();
    auto f_pos = f2->get_position();
    auto g_pos = g2->get_position();


    REQUIRE(c_pos.first == -1);
    REQUIRE(c_pos.second == 0);
    REQUIRE(d_pos.first ==-1);
    REQUIRE(d_pos.second == 1);
    REQUIRE(e_pos.first == 0);
    REQUIRE(e_pos.second == 2);
    REQUIRE(f_pos.first == 1);
    REQUIRE(f_pos.second == 2);
    REQUIRE(g_pos.first == 1);
    REQUIRE(g_pos.second == 1);
}


TEST_CASE("Test multiple,2nd lvl tilted 1 emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*b1,*c2,*d2,*e2,*f2,*g2;
    REQUIRE((a1 = hex.emplace(1)) != nullptr);
    REQUIRE((c2 = a1->emplace(0)) != nullptr);
    REQUIRE((d2 = a1->emplace(1)) != nullptr);
    REQUIRE((e2 = a1->emplace(2)) != nullptr);
    REQUIRE((f2 = a1->emplace(3)) != nullptr);
    REQUIRE((g2 = a1->emplace(4)) != nullptr);

    auto c_pos = c2->get_position();
    auto d_pos = d2->get_position();
    auto e_pos = e2->get_position();
    auto f_pos = f2->get_position();
    auto g_pos = g2->get_position();


    REQUIRE(c_pos.first == 0);
    REQUIRE(c_pos.second == 1);
    REQUIRE(d_pos.first ==1);
    REQUIRE(d_pos.second == 2);
    REQUIRE(e_pos.first == 2);
    REQUIRE(e_pos.second == 2);
    REQUIRE(f_pos.first == 2);
    REQUIRE(f_pos.second == 1);
    REQUIRE(g_pos.first == 1);
    REQUIRE(g_pos.second == 0);
}


TEST_CASE("Test multiple,2nd lvl tilted 3 emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*c2,*d2,*e2,*f2,*g2;
    REQUIRE((a1 = hex.emplace(3)) != nullptr);
    REQUIRE((c2 = a1->emplace(0)) != nullptr);
    REQUIRE((d2 = a1->emplace(1)) != nullptr);
    REQUIRE((e2 = a1->emplace(2)) != nullptr);
    REQUIRE((f2 = a1->emplace(3)) != nullptr);
    REQUIRE((g2 = a1->emplace(4)) != nullptr);

    auto c_pos = c2->get_position();
    auto d_pos = d2->get_position();
    auto e_pos = e2->get_position();
    auto f_pos = f2->get_position();
    auto g_pos = g2->get_position();

    REQUIRE(c_pos.first == 1);
    REQUIRE(c_pos.second == 0);
    REQUIRE(d_pos.first ==1);
    REQUIRE(d_pos.second == -1);
    REQUIRE(e_pos.first == 0);
    REQUIRE(e_pos.second == -2);
    REQUIRE(f_pos.first == -1);
    REQUIRE(f_pos.second == -2);
    REQUIRE(g_pos.first == -1);
    REQUIRE(g_pos.second == -1);
}


TEST_CASE("Test multiple,2nd lvl tilted 4 emplace + position","[HEX]")
{
    hexagon hex = hexagon::prepare_grid();
    hexagon *a1,*b1,*c2,*d2,*e2,*f2,*g2,*h1;
    REQUIRE((a1 = hex.emplace(4)) != nullptr);
    REQUIRE((c2 = a1->emplace(0)) != nullptr);
    REQUIRE((d2 = a1->emplace(1)) != nullptr);
    REQUIRE((e2 = a1->emplace(2)) != nullptr);
    REQUIRE((f2 = a1->emplace(3)) != nullptr);
    REQUIRE((g2 = a1->emplace(4)) != nullptr);

    auto c_pos = c2->get_position();
    auto d_pos = d2->get_position();
    auto e_pos = e2->get_position();
    auto f_pos = f2->get_position();
    auto g_pos = g2->get_position();


    REQUIRE(c_pos.first == 0);
    REQUIRE(c_pos.second == -1);
    REQUIRE(d_pos.first ==-1);
    REQUIRE(d_pos.second == -2);
    REQUIRE(e_pos.first == -2);
    REQUIRE(e_pos.second == -2);
    REQUIRE(f_pos.first == -2);
    REQUIRE(f_pos.second == -1);
    REQUIRE(g_pos.first == -1);
    REQUIRE(g_pos.second == 0);
}