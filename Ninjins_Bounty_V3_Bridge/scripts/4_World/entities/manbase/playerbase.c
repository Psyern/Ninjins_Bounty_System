modded class PlayerBase
{
	override bool obfm_MayRunBountyAdminTools()
	{
		NinjinsUpgraded_PermGate permGate;

		if (super.obfm_MayRunBountyAdminTools())
			return true;
		permGate = GetNinjinsUpgradedPermGate();
		if (!permGate)
			return false;
		if (!GetIdentity())
			return false;
		if (permGate.HasPermission(NinjinsUpgraded_PermissionIds.ADMIN_MENU_ACCESS, GetIdentity()))
			return true;
		return false;
	}

	override bool obfm_BountyPlayerInPvEZone()
	{
		return NinjinsUpgraded_IsInPvEZone();
	}

	override bool obfm_NinjinBountyIsPlayerInNinjinsSafeZone()
	{
		return NinjinsUpgraded_IsInSafeZone();
	}

	override bool obfm_NinjinBountyIsOnSafeZoneExitTimer()
	{
		return NinjinsUpgraded_SafeExitActive();
	}

	override bool NinjinsUpgraded_ZoneHitOpen(EntityAI source, TotalDamageResult damageResult, int damageType, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		obfc_BountyDamageHandler bountyHandler;
		PlayerBase attackerPlayer;
		bool openHit;
		bool bountyDecided;

		openHit = false;
		bountyDecided = false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return super.NinjinsUpgraded_ZoneHitOpen(source, damageResult, damageType, component, dmgZone, ammo, modelPos, speedCoef);
		attackerPlayer = NinjinsUpgraded_DamageOp.PlayerFromDamageSource(source);
		if (!attackerPlayer)
			return super.NinjinsUpgraded_ZoneHitOpen(source, damageResult, damageType, component, dmgZone, ammo, modelPos, speedCoef);
		#ifdef EXPANSIONMODAI
		if (attackerPlayer.IsInherited(eAIBase) || IsInherited(eAIBase))
			return super.NinjinsUpgraded_ZoneHitOpen(source, damageResult, damageType, component, dmgZone, ammo, modelPos, speedCoef);
		#endif
		bountyHandler = obfc_BountyDamageHandler.GetInstance();
		bountyDecided = bountyHandler.obfm_TryOpenDeniedZoneHit(this, attackerPlayer, openHit);
		if (bountyDecided)
			return openHit;
		return super.NinjinsUpgraded_ZoneHitOpen(source, damageResult, damageType, component, dmgZone, ammo, modelPos, speedCoef);
	}
}
