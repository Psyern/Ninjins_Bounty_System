modded class NinjinsUpgraded_AdminModRegHook
{
	override void AppendPanelModules(array<ref NinjinsUpgraded_AdminModBase> modules)
	{
		super.AppendPanelModules(modules);
		if (!modules)
			return;
		modules.Insert(new NinjinsBntyV3_AdmMod());
	}
}

modded class NinjinsUpgraded_AdminShell
{
	NinjinsBntyV3_AdmMod FindBountyV3BridgeModule()
	{
		array<ref NinjinsUpgraded_AdminModBase> modules;
		int moduleIndex;
		NinjinsBntyV3_AdmMod oneModule;

		modules = NinjinsUpgraded_AdminModReg.GetPanelModules();
		if (!modules)
			return null;
		for (moduleIndex = 0; moduleIndex < modules.Count(); moduleIndex++)
		{
			oneModule = NinjinsBntyV3_AdmMod.Cast(modules.Get(moduleIndex));
			if (oneModule)
				return oneModule;
		}
		return null;
	}

	NinjinsBntyV3_AdmForm FindBountyV3BridgeForm()
	{
		NinjinsBntyV3_AdmMod oneModule;

		oneModule = FindBountyV3BridgeModule();
		if (!oneModule)
			return null;
		return NinjinsBntyV3_AdmForm.Cast(oneModule.GetForm());
	}

	override void OnAdminReopened()
	{
		NinjinsBntyV3_AdmMod bountyModule;

		super.OnAdminReopened();
		bountyModule = FindBountyV3BridgeModule();
		if (bountyModule)
			bountyModule.RequestConfigFromServer();
	}
}
