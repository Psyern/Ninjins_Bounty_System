modded class MissionServer
{
	protected bool m_NinjinsBntyV3_AdminRpcHooked;

	override void OnInit()
	{
		super.OnInit();
		if (!g_Game || !g_Game.IsServer())
			return;
		NinjinsBntyV3_HookAdminServerRpc();
	}

	override void NinjinsUpgraded_CoreReloadMainAndActions()
	{
		super.NinjinsUpgraded_CoreReloadMainAndActions();
		obfv_g_BountyConfig = obfc_BountyConfig.obfm_LoadConfig();
		NinjinsUpgraded_Log.Info("[Reload] Bounty System (v3 bridge): " + obfv_Ninjins_Bounty_System_CONFIG_FILE);
	}

	protected void NinjinsBntyV3_HookAdminServerRpc()
	{
		if (m_NinjinsBntyV3_AdminRpcHooked)
			return;
		GetRPCManager().AddRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_AskCfg", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_SaveCfg", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_ReloadCfg", this, SingleplayerExecutionType.Server);
		m_NinjinsBntyV3_AdminRpcHooked = true;
	}

	protected void NinjinsBntyV3_SendCfgToClient(PlayerIdentity recipient)
	{
		Param1<ref obfc_BountyConfig> payload;

		if (!recipient)
			return;
		if (!obfv_g_BountyConfig)
			obfv_g_BountyConfig = obfc_BountyConfig.obfm_LoadConfig();
		payload = new Param1<ref obfc_BountyConfig>(obfv_g_BountyConfig);
		GetRPCManager().SendRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_RecvCfg", payload, true, recipient);
	}

	protected void NinjinsBntyV3_SendSaveResult(PlayerIdentity recipient, bool saved)
	{
		Param1<bool> payload;

		if (!recipient)
			return;
		payload = new Param1<bool>(saved);
		GetRPCManager().SendRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_RecvSave", payload, true, recipient);
	}

	void NinjinsBntyV3_AskCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Server)
			return;
		if (!NinjinsUpgraded_AdmCfgHost.SenderMayOpenAdminMenu(sender))
			return;
		NinjinsBntyV3_SendCfgToClient(sender);
	}

	void NinjinsBntyV3_SaveCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<ref obfc_BountyConfig> payload;
		bool saved;

		if (type != CallType.Server)
			return;
		if (!NinjinsUpgraded_AdmCfgHost.SenderMayEditCoreConfig(sender))
			return;
		if (!ctx.Read(payload))
			return;
		if (!payload.param1)
			return;
		payload.param1.obfm_ValidateConfig();
		payload.param1.obfm_SaveConfig();
		obfv_g_BountyConfig = payload.param1;
		saved = true;
		NinjinsBntyV3_SendSaveResult(sender, saved);
		NinjinsBntyV3_SendCfgToClient(sender);
	}

	void NinjinsBntyV3_ReloadCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Server)
			return;
		if (!NinjinsUpgraded_AdmCfgHost.SenderMayEditCoreConfig(sender))
			return;
		obfc_BountyManager.obfm_ReloadAllConfigs(null);
		NinjinsBntyV3_SendCfgToClient(sender);
	}
}
