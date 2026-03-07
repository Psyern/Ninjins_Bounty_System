class CfgPatches
{
	class Ninjins_Bounty_Token
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Ninjins_Bounty_Token_Silver: Inventory_Base
	{
		scope = 2;
		displayName = "Ninjins Silver Bounty Token";
		descriptionShort="A Token to activate a bouty on a player.";
		model = "Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Ninjins_Bounty_Token.p3d";
		itemSize[] = {2,2};
		weight = 1000;
		rotationFlags = 16;
		overrideDrawArea = "25.0";
		forceFarBubble = "true";
		varQuantityMax = 50;
		varQuantityInit = 1;
		varQuantityDestroyOnMin = 0;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = 
		{
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Silver.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Silver.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Silver.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000000;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class Ninjins_Bounty_Token_Gold: Ninjins_Bounty_Token_Silver
	{
		scope = 2;
		displayName = "Ninjins Gold Bounty Token";
		descriptionShort="A Token to activate a bouty on a player.";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = 
		{
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Gold.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Gold.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Gold.paa"
		};
	};
	class Ninjins_Bounty_Token_Red: Ninjins_Bounty_Token_Silver
	{
		scope = 2;
		displayName = "Ninjins Red Bounty Token";
		descriptionShort="A Token to activate a bouty on a player.";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = 
		{
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Red.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Red.paa",
			"Ninjins_Bounty_System\data\Ninjins_Bounty_Token\Textures\Ninjins_Bounty_Token_Red.paa"
		};
	};
};