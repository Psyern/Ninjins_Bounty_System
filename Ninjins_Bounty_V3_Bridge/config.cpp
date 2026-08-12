//! Wires Ninjins_Bounty_System into Ninjins Upgraded v3 (Core + Zones).
//! Load: Core + Zones + Ninjins_Bounty_System + this bridge. Do not also load Ninjins_Advanced_Bounty.
class CfgPatches
{
	class Ninjins_Bounty_V3_Bridge
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data","Ninjins_Bounty_System","Ninjins_Core","Ninjins_PvP_PvE_Upgraded_Zones"};
	};
};

class CfgMods
{
	class Ninjins_Bounty_V3_Bridge
	{
		dir="Ninjins_Bounty_V3_Bridge";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ninjins Bounty V3 Bridge";
		credits="Ninjin";
		author="Ninjin";
		authorID="0";
		version="1.0.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"Ninjins_Bounty_V3_Bridge/scripts/Common",
					"Ninjins_Bounty_V3_Bridge/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"Ninjins_Bounty_V3_Bridge/scripts/Common",
					"Ninjins_Bounty_V3_Bridge/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"Ninjins_Bounty_V3_Bridge/scripts/Common",
					"Ninjins_Bounty_V3_Bridge/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
};
