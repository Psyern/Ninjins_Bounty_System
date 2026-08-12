modded class MissionGameplay
{
	protected bool m_NinjinsBntyV3_ClientAdminRpcHooked;

	override void OnInit()
	{
		super.OnInit();
		NinjinsBntyV3_HookClientAdminRpc();
	}

	protected void NinjinsBntyV3_HookClientAdminRpc()
	{
		if (m_NinjinsBntyV3_ClientAdminRpcHooked)
			return;
		if (!g_Game || !g_Game.IsClient())
			return;
		GetRPCManager().AddRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_RecvCfg", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_RecvSave", this, SingleplayerExecutionType.Client);
		m_NinjinsBntyV3_ClientAdminRpcHooked = true;
	}

	void NinjinsBntyV3_RecvCfg(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<ref obfc_BountyConfig> payload;
		NinjinsBntyV3_AdmForm form;

		if (type != CallType.Client)
			return;
		if (!ctx.Read(payload))
			return;
		form = GetNinjinsUpgradedAdminShell().FindBountyV3BridgeForm();
		if (!form)
			return;
		form.LoadConfigFromServer(payload.param1);
	}

	void NinjinsBntyV3_RecvSave(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<bool> payload;
		NinjinsBntyV3_AdmForm form;

		if (type != CallType.Client)
			return;
		if (!ctx.Read(payload))
			return;
		form = GetNinjinsUpgradedAdminShell().FindBountyV3BridgeForm();
		if (!form)
			return;
		form.OnSaveResultFromServer(payload.param1);
	}

	override void obfm_OnBountyAdminPlayersReceived(array<string> players)
	{
		NinjinsBntyV3_AdmForm bountyForm;

		super.obfm_OnBountyAdminPlayersReceived(players);
		bountyForm = GetNinjinsUpgradedAdminShell().FindBountyV3BridgeForm();
		if (bountyForm)
			bountyForm.FillOnlinePlayersFromServer(players);
	}

	override void obfm_OnBountyAdminBlacklistReceived(array<string> blacklistedPlayers)
	{
		NinjinsBntyV3_AdmForm bountyForm;

		super.obfm_OnBountyAdminBlacklistReceived(blacklistedPlayers);
		bountyForm = GetNinjinsUpgradedAdminShell().FindBountyV3BridgeForm();
		if (bountyForm)
			bountyForm.FillBlacklistFromServer(blacklistedPlayers);
	}
}
