class CfgPatches
{
	class Ninjins_Bounty_System
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data",
			"DZ_Gear_Camping",
		};
	};
};
class CfgMods
{
	class Ninjins_Bounty_System
	{
		dir="Ninjins_Bounty_System";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		inputs = "Ninjins_Bounty_System/data/inputs.xml";
		name="Ninjins_Bounty_System";
		credits="Naij0";
		author="Naij0";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		storageVersion = 1;
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
					"Ninjins_Bounty_System/scripts/Common",
					"Ninjins_Bounty_System/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"Ninjins_Bounty_System/scripts/Common",
					"Ninjins_Bounty_System/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"Ninjins_Bounty_System/scripts/Common",
					"Ninjins_Bounty_System/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class SeaChest;
	class HouseNoDestruct;
	class Ninjins_Bounty_Board_Static: HouseNoDestruct
	{
		scope=2;
		model="Ninjins_Bounty_System\Data\Ninjins_Bounty_Board\Ninjins_Bounty_Board.p3d";
	};
	class NinjinsBountyCrate_Base: SeaChest
	{
		scope=0;
		displayName="Ninjins Bounty Crate";
		descriptionShort="Ninjins Bounty Crate";
		model="Ninjins_Bounty_System\Data\Ninjins_Bounty_Crate\Ninjins_Bounty_Crate.p3d";
		weight=10000;
		itemBehaviour=2;
		itemSize[]={11,11};
		class Cargo
		{
			itemsCargoSize[]={10,10};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class NinjinsBountyCrate_250: NinjinsBountyCrate_Base
	{
		scope=2;
		class Cargo
		{
			itemsCargoSize[]={10,25};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class NinjinsBountyCrate_500: NinjinsBountyCrate_Base
	{
		scope=2;
		class Cargo
		{
			itemsCargoSize[]={10,50};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class NinjinsBountyCrate_1000: NinjinsBountyCrate_Base
	{
		scope=2;
		class Cargo
		{
			itemsCargoSize[]={10,100};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
};