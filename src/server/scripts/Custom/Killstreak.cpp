/*
 * Copyright (C) 2013-2015 DeathCore <http://www.noffearrdeathproject.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
     
    #include "ScriptPCH.h"
     
    class System_OnKill : public PlayerScript
    {
    public:
        System_OnKill() : PlayerScript("System_OnKill") {}
     
        void OnPVPKill(Player * Killer, Player * Victim)
        {
            uint32 KillerGUID = Killer->GetGUIDLow();
            uint32 VictimGUID = Victim->GetGUIDLow();
     
            struct KillStreak_Info
            {
                uint32 killstreak;
                uint32 lastkill;
            };
     
            static std::map<uint32, KillStreak_Info> KillStreakData;
     
            if (KillerGUID == VictimGUID || KillStreakData[KillerGUID].lastkill == VictimGUID)
                return;
     
            if (KillStreakData[VictimGUID].killstreak >= 3)
            {
                std::ostringstream ss;
                ss << "|cFF81CF42" << Killer->GetName() << "|r has ended |cFFFFFFFF" << Victim->GetName() << "|r's killing spree!";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }
     
            ++KillStreakData[KillerGUID].killstreak;
            KillStreakData[KillerGUID].lastkill = VictimGUID;
            KillStreakData[VictimGUID].killstreak = 0;
            KillStreakData[VictimGUID].lastkill = 0;
     
            if (KillStreakData[KillerGUID].killstreak % 10 == 0) // send killstreak message every 10 kills
            {
                std::ostringstream ss;
                ss << "|cFF81CF42" << Killer->GetName() << "|r has a killstreak of |cFF42A0CF" << KillStreakData[KillerGUID].killstreak << "|r!";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }
            else if (KillStreakData[KillerGUID].killstreak == 3)
            {
                std::ostringstream ss;
                ss << "|cFF81CF42" << Killer->GetName() << "|r is on a killingspree!";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }
     
        }
    };
     
    void AddSC_PvP_System()
    {
        new System_OnKill;
    }

