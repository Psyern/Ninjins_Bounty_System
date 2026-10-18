const string obfv_Ninjins_Bounty_System_LOOT_PRESET_CONFIG_FILE = obfv_Ninjins_Bounty_System_CONFIG_DIR + "BountyLootPresets.json";
ref obfc_BountyLootPresetConfig obfv_g_BountyLootPresetConfig;
//! One admin loot reward: every item of the list spawns into the container when the killer claims it.
class obfc_BountyLootPreset
{
	string Name;
	string ContainerClassName;
	bool RuinedContainer;
	ref array<ref obfc_BountyRewardItem> Items;
	void obfc_BountyLootPreset()
	{
		Name = "";
		ContainerClassName = "NinjinsBountyCrate_250";
		RuinedContainer = true;
		Items = new array<ref obfc_BountyRewardItem>;
	}
	void obfm_AddItem(string className)
	{
		obfc_BountyRewardItem item;
		item = new obfc_BountyRewardItem();
		item.ItemClassName = className;
		Items.Insert(item);
	}
}
class obfc_BountyLootPresetConfig
{
	ref array<ref obfc_BountyLootPreset> Presets;
	void obfc_BountyLootPresetConfig()
	{
		Presets = new array<ref obfc_BountyLootPreset>;
	}
	void obfm_AddDefaultPresets()
	{
		obfc_BountyLootPreset marksman;
		obfc_BountyLootPreset medic;
		marksman = new obfc_BountyLootPreset();
		marksman.Name = "Marksman";
		marksman.obfm_AddItem("SVD");
		marksman.obfm_AddItem("PSO1Optic");
		marksman.obfm_AddItem("Mag_SVD_10Rnd");
		marksman.obfm_AddItem("Mag_SVD_10Rnd");
		Presets.Insert(marksman);
		medic = new obfc_BountyLootPreset();
		medic.Name = "Medic";
		medic.obfm_AddItem("SalineBagIV");
		medic.obfm_AddItem("Morphine");
		medic.obfm_AddItem("Epinephrine");
		medic.obfm_AddItem("BandageDressing");
		medic.obfm_AddItem("BandageDressing");
		Presets.Insert(medic);
	}
	obfc_BountyLootPreset obfm_FindPreset(string presetName)
	{
		string wanted;
		string current;
		wanted = presetName;
		wanted.ToLower();
		foreach (obfc_BountyLootPreset preset : Presets)
		{
			if (!preset)
				continue;
			current = preset.Name;
			current.ToLower();
			if (current == wanted)
				return preset;
		}
		return null;
	}
	string obfm_GetPresetNames()
	{
		string names;
		names = "";
		foreach (obfc_BountyLootPreset preset : Presets)
		{
			if (!preset)
				continue;
			if (names != "")
				names = names + ", ";
			names = names + preset.Name;
		}
		return names;
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
			return;
		obfc_BountyConfig.obfm_CheckDirectories();
		JsonFileLoader<obfc_BountyLootPresetConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_LOOT_PRESET_CONFIG_FILE, this);
	}
	static obfc_BountyLootPresetConfig obfm_LoadConfig()
	{
		obfc_BountyLootPresetConfig config;
		if (IsMissionClient())
			return null;
		obfc_BountyConfig.obfm_CheckDirectories();
		config = new obfc_BountyLootPresetConfig();
		if (FileExist(obfv_Ninjins_Bounty_System_LOOT_PRESET_CONFIG_FILE))
		{
			JsonFileLoader<obfc_BountyLootPresetConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_LOOT_PRESET_CONFIG_FILE, config);
			if (!config.Presets)
				config.Presets = new array<ref obfc_BountyLootPreset>;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyLootPresets loaded from file: " + config.Presets.Count().ToString() + " preset(s) - " + config.obfm_GetPresetNames());
			return config;
		}
		config.obfm_AddDefaultPresets();
		config.obfm_SaveConfig();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyLootPresets.json not found. Created default presets: " + config.obfm_GetPresetNames());
		return config;
	}
}
