#pragma once

namespace ai
{
    class Event
	{
	public:
        Event(Event const& other):source(other.source), param(other.param),packet(other.packet), owner(other.owner)
        {
           // source = other.source;
           // param = other.param;
           // packet = other.packet;
           // owner = other.owner;
        }
        Event() {}
        Event(string source) : source(source) {}
        Event(string source, string param, Player* owner = NULL) : source(source), param(param), owner(owner) {}
        Event(string source, WorldPacket &packet, Player* owner = NULL) : source(source), packet(packet), owner(owner) {}
        virtual ~Event() {}

	public:
        string getSource() { return source; }
        string getParam() { return param; }
		void setSource(string src) { source = src; }
		void setParam(string par) { param = par; }
        WorldPacket& getPacket() { return packet; }
		void setPacket(WorldPacket& pct) { packet = std::move(pct); }
        ObjectGuid getObject();
        Player* getOwner() { return owner; }
		void setOwner(Player* pl) { owner = pl; }
        bool operator! () const { return source.empty(); }

    protected:
        string source;
        string param;
        WorldPacket packet;
        ObjectGuid object;
        Player* owner;
	};
}
