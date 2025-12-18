#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>
#include <vector>

enum class NPCType {
    Bear,
    Elf,
    Rogue
};

class NPCVisitor;

class NPC {
public:
    NPC(NPCType type, int x, int y, const std::string& name);
    virtual ~NPC() = default;
    
    virtual void accept(NPCVisitor& visitor) = 0;
    
    NPCType getType() const;
    int getX() const;
    int getY() const;
    const std::string& getName() const;
    bool isAlive() const;
    void markDead();

private:
    NPCType type;
    int x;
    int y;
    std::string name;
    bool alive;
};

class Bear : public NPC {
public:
    Bear(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
};

class Elf : public NPC {
public:
    Elf(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
};

class Rogue : public NPC {
public:
    Rogue(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
};

#endif