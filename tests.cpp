#include "gtest/gtest.h"
#include "dungeon_editor.h"
#include "factory.h"
#include <fstream>
#include <filesystem>

class DungeonEditorTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream testFile("test_dungeon.txt");
        testFile << "Bear 10 10 Bear1\n";
        testFile << "Elf 20 20 Elf1\n";
        testFile << "Rogue 30 30 Rogue1\n";
        testFile.close();
    }
    
    void TearDown() override {
        std::remove("test_dungeon.txt");
        std::remove("test_save.txt");
        std::remove("log.txt");
    }
};

TEST_F(DungeonEditorTest, AddNPC) {
    DungeonEditor editor;
    editor.addNPC(NPCType::Bear, 100, 100, "TestBear");
    editor.addNPC(NPCType::Elf, 200, 200, "TestElf");
    
    auto npcs = editor.getNPCs();
    ASSERT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getName(), "TestBear");
    EXPECT_EQ(npcs[1]->getName(), "TestElf");
}

TEST_F(DungeonEditorTest, AddNPCOutOfBounds) {
    DungeonEditor editor;
    EXPECT_THROW(editor.addNPC(NPCType::Bear, 600, 100, "BadBear"), std::runtime_error);
    EXPECT_THROW(editor.addNPC(NPCType::Elf, 100, -50, "BadElf"), std::runtime_error);
}

TEST_F(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor1;
    editor1.addNPC(NPCType::Bear, 10, 10, "Bear1");
    editor1.addNPC(NPCType::Elf, 20, 20, "Elf1");
    
    editor1.save("test_save.txt");
    
    DungeonEditor editor2;
    editor2.load("test_save.txt");
    
    auto npcs = editor2.getNPCs();
    ASSERT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getName(), "Bear1");
    EXPECT_EQ(npcs[1]->getName(), "Elf1");
}

TEST_F(DungeonEditorTest, LoadFromFile) {
    DungeonEditor editor;
    editor.load("test_dungeon.txt");
    
    auto npcs = editor.getNPCs();
    ASSERT_EQ(npcs.size(), 3);
    EXPECT_EQ(npcs[0]->getName(), "Bear1");
    EXPECT_EQ(npcs[1]->getName(), "Elf1");
    EXPECT_EQ(npcs[2]->getName(), "Rogue1");
}

TEST_F(DungeonEditorTest, BattleElfKillsRogue) {
    DungeonEditor editor;
    editor.addNPC(NPCType::Elf, 100, 100, "Elf1");
    editor.addNPC(NPCType::Rogue, 101, 101, "Rogue1");
    
    editor.battle(10);
    
    auto npcs = editor.getNPCs();
    EXPECT_FALSE(npcs[1]->isAlive());
    EXPECT_TRUE(npcs[0]->isAlive());
}

TEST_F(DungeonEditorTest, BattleBearKillsElf) {
    DungeonEditor editor;
    editor.addNPC(NPCType::Bear, 100, 100, "Bear1");
    editor.addNPC(NPCType::Elf, 101, 101, "Elf1");
    
    editor.battle(10);
    
    auto npcs = editor.getNPCs();
    EXPECT_FALSE(npcs[1]->isAlive());
    EXPECT_TRUE(npcs[0]->isAlive());
}

TEST_F(DungeonEditorTest, BattleOutOfRange) {
    DungeonEditor editor;
    editor.addNPC(NPCType::Elf, 100, 100, "Elf1");
    editor.addNPC(NPCType::Rogue, 200, 200, "Rogue1");
    
    editor.battle(10);
    
    auto npcs = editor.getNPCs();
    EXPECT_TRUE(npcs[0]->isAlive());
    EXPECT_TRUE(npcs[1]->isAlive());
}

TEST_F(DungeonEditorTest, FactoryCreate) {
    auto bear = NPCFactory::create(NPCType::Bear, 1, 1, "Bear");
    auto elf = NPCFactory::create(NPCType::Elf, 2, 2, "Elf");
    auto rogue = NPCFactory::create(NPCType::Rogue, 3, 3, "Rogue");
    
    EXPECT_EQ(bear->getType(), NPCType::Bear);
    EXPECT_EQ(elf->getType(), NPCType::Elf);
    EXPECT_EQ(rogue->getType(), NPCType::Rogue);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}