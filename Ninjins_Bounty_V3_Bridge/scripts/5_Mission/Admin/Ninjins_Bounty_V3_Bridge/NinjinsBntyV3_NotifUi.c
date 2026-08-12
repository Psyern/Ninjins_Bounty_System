//! Notification + broadcast editors for bounty v3 sidebar (matches v2 admin menu coverage).
class NinjinsBntyV3_NotifUi
{
	ref NinjinsBntyV3_MsgRow m_PlacedHunted;
	ref NinjinsBntyV3_MsgRow m_PlacedExpired;
	ref NinjinsBntyV3_MsgRow m_PlacedSurvival;
	ref NinjinsBntyV3_MsgRow m_PlacedKilled;
	ref NinjinsBntyV3_MsgRow m_RuleHunted;
	ref NinjinsBntyV3_MsgRow m_RuleHitWarn;
	ref NinjinsBntyV3_MsgRow m_RuleExpired;
	ref NinjinsBntyV3_MsgRow m_RuleSurvival;
	ref NinjinsBntyV3_MsgRow m_RuleKilled;
	ref NinjinsBntyV3_MsgRow m_OtherTokens;
	ref NinjinsBntyV3_MsgRow m_OtherSkipNone;
	ref NinjinsBntyV3_MsgRow m_OtherSkipOk;
	ref NinjinsBntyV3_MsgRow m_OtherSkipped;
	ref NinjinsBntyV3_MsgRow m_OtherHands;
	ref NinjinsBntyV3_MsgRow m_OtherCooldown;
	ref NinjinsBntyV3_MsgRow m_OtherSafe;
	ref NinjinsBntyV3_MsgRow m_OtherPersist;
	ref NinjinsBntyV3_MsgRow m_OtherTeleport;
	ref NinjinsBntyV3_MsgRow m_OtherPauseTerr;
	ref NinjinsBntyV3_MsgRow m_OtherPauseSafe;
	ref NinjinsBntyV3_MsgRow m_BcPlaced;
	ref NinjinsBntyV3_MsgRow m_BcRule;
	ref NinjinsBntyV3_MsgRow m_BcExpired;
	ref NinjinsBntyV3_MsgRow m_BcWin;
	ref NinjinsBntyV3_MsgRow m_BcSuicide;
	ref NinjinsBntyV3_MsgRow m_BcLogout;
	ref NinjinsBntyV3_MsgRow m_BcWarning;

	protected NinjinsBntyV3_MsgRow NewRow(NinjinsUpgraded_AdmDynForm form, string labelPrefix)
	{
		NinjinsBntyV3_MsgRow row;

		row = new NinjinsBntyV3_MsgRow();
		row.Layout(form, labelPrefix);
		return row;
	}

	void Layout(NinjinsUpgraded_AdmDynForm form)
	{
		if (!form)
			return;

		form.AddSectionTitle("Notifications - Placed bounty", false, "notifPlaced");
		m_PlacedHunted = NewRow(form, "Placed hunted");
		m_PlacedExpired = NewRow(form, "Placed expired");
		m_PlacedSurvival = NewRow(form, "Placed survival reward");
		m_PlacedKilled = NewRow(form, "Placed killed reward");

		form.AddSectionTitle("Notifications - Rule breaker", false, "notifRule");
		m_RuleHunted = NewRow(form, "Rule breaker hunted");
		m_RuleHitWarn = NewRow(form, "Rule breaker hit warning");
		m_RuleExpired = NewRow(form, "Rule breaker expired");
		m_RuleSurvival = NewRow(form, "Rule breaker survival reward");
		m_RuleKilled = NewRow(form, "Rule breaker killed reward");

		form.AddSectionTitle("Notifications - Other", false, "notifOther");
		m_OtherTokens = NewRow(form, "Insufficient tokens");
		m_OtherSkipNone = NewRow(form, "Skip bounty no players");
		m_OtherSkipOk = NewRow(form, "Skip bounty success");
		m_OtherSkipped = NewRow(form, "Bounty skipped");
		m_OtherHands = NewRow(form, "Reward hands not free");
		m_OtherCooldown = NewRow(form, "Player on cooldown");
		m_OtherSafe = NewRow(form, "Player in safe zone");
		m_OtherPersist = NewRow(form, "Bounty persisted");
		m_OtherTeleport = NewRow(form, "Teleported out of territory");
		m_OtherPauseTerr = NewRow(form, "Bounty paused in territory");
		m_OtherPauseSafe = NewRow(form, "Bounty paused in safe zone");

		form.AddSectionTitle("Broadcasts", false, "broadcasts");
		m_BcPlaced = NewRow(form, "Broadcast placed bounty");
		m_BcRule = NewRow(form, "Broadcast rule breaker");
		m_BcExpired = NewRow(form, "Broadcast expired");
		m_BcWin = NewRow(form, "Broadcast win");
		m_BcSuicide = NewRow(form, "Broadcast suicide");
		m_BcLogout = NewRow(form, "Broadcast logout");
		m_BcWarning = NewRow(form, "Broadcast warning");
	}

	void Destroy()
	{
		if (m_PlacedHunted)
			m_PlacedHunted.Destroy();
		if (m_PlacedExpired)
			m_PlacedExpired.Destroy();
		if (m_PlacedSurvival)
			m_PlacedSurvival.Destroy();
		if (m_PlacedKilled)
			m_PlacedKilled.Destroy();
		if (m_RuleHunted)
			m_RuleHunted.Destroy();
		if (m_RuleHitWarn)
			m_RuleHitWarn.Destroy();
		if (m_RuleExpired)
			m_RuleExpired.Destroy();
		if (m_RuleSurvival)
			m_RuleSurvival.Destroy();
		if (m_RuleKilled)
			m_RuleKilled.Destroy();
		if (m_OtherTokens)
			m_OtherTokens.Destroy();
		if (m_OtherSkipNone)
			m_OtherSkipNone.Destroy();
		if (m_OtherSkipOk)
			m_OtherSkipOk.Destroy();
		if (m_OtherSkipped)
			m_OtherSkipped.Destroy();
		if (m_OtherHands)
			m_OtherHands.Destroy();
		if (m_OtherCooldown)
			m_OtherCooldown.Destroy();
		if (m_OtherSafe)
			m_OtherSafe.Destroy();
		if (m_OtherPersist)
			m_OtherPersist.Destroy();
		if (m_OtherTeleport)
			m_OtherTeleport.Destroy();
		if (m_OtherPauseTerr)
			m_OtherPauseTerr.Destroy();
		if (m_OtherPauseSafe)
			m_OtherPauseSafe.Destroy();
		if (m_BcPlaced)
			m_BcPlaced.Destroy();
		if (m_BcRule)
			m_BcRule.Destroy();
		if (m_BcExpired)
			m_BcExpired.Destroy();
		if (m_BcWin)
			m_BcWin.Destroy();
		if (m_BcSuicide)
			m_BcSuicide.Destroy();
		if (m_BcLogout)
			m_BcLogout.Destroy();
		if (m_BcWarning)
			m_BcWarning.Destroy();
		m_PlacedHunted = null;
		m_PlacedExpired = null;
		m_PlacedSurvival = null;
		m_PlacedKilled = null;
		m_RuleHunted = null;
		m_RuleHitWarn = null;
		m_RuleExpired = null;
		m_RuleSurvival = null;
		m_RuleKilled = null;
		m_OtherTokens = null;
		m_OtherSkipNone = null;
		m_OtherSkipOk = null;
		m_OtherSkipped = null;
		m_OtherHands = null;
		m_OtherCooldown = null;
		m_OtherSafe = null;
		m_OtherPersist = null;
		m_OtherTeleport = null;
		m_OtherPauseTerr = null;
		m_OtherPauseSafe = null;
		m_BcPlaced = null;
		m_BcRule = null;
		m_BcExpired = null;
		m_BcWin = null;
		m_BcSuicide = null;
		m_BcLogout = null;
		m_BcWarning = null;
	}

	void LoadFromConfig(obfc_BountyConfig cfg)
	{
		if (!cfg)
			return;
		if (cfg.Notifications)
		{
			if (cfg.Notifications.PlacedBounty)
			{
				if (m_PlacedHunted)
					m_PlacedHunted.LoadNotif(cfg.Notifications.PlacedBounty.Hunted);
				if (m_PlacedExpired)
					m_PlacedExpired.LoadNotif(cfg.Notifications.PlacedBounty.Expired);
				if (m_PlacedSurvival)
					m_PlacedSurvival.LoadNotif(cfg.Notifications.PlacedBounty.SurvivalReward);
				if (m_PlacedKilled)
					m_PlacedKilled.LoadNotif(cfg.Notifications.PlacedBounty.KilledReward);
			}
			if (cfg.Notifications.RuleBreaker)
			{
				if (m_RuleHunted)
					m_RuleHunted.LoadNotif(cfg.Notifications.RuleBreaker.Hunted);
				if (m_RuleHitWarn)
					m_RuleHitWarn.LoadNotif(cfg.Notifications.RuleBreaker.HitWarning);
				if (m_RuleExpired)
					m_RuleExpired.LoadNotif(cfg.Notifications.RuleBreaker.Expired);
				if (m_RuleSurvival)
					m_RuleSurvival.LoadNotif(cfg.Notifications.RuleBreaker.SurvivalReward);
				if (m_RuleKilled)
					m_RuleKilled.LoadNotif(cfg.Notifications.RuleBreaker.KilledReward);
			}
			if (cfg.Notifications.Other)
			{
				if (m_OtherTokens)
					m_OtherTokens.LoadNotif(cfg.Notifications.Other.InsufficientTokens);
				if (m_OtherSkipNone)
					m_OtherSkipNone.LoadNotif(cfg.Notifications.Other.SkipBountyNoPlayers);
				if (m_OtherSkipOk)
					m_OtherSkipOk.LoadNotif(cfg.Notifications.Other.SkipBountySuccess);
				if (m_OtherSkipped)
					m_OtherSkipped.LoadNotif(cfg.Notifications.Other.BountySkipped);
				if (m_OtherHands)
					m_OtherHands.LoadNotif(cfg.Notifications.Other.RewardHandsNotFree);
				if (m_OtherCooldown)
					m_OtherCooldown.LoadNotif(cfg.Notifications.Other.PlayerOnCooldown);
				if (m_OtherSafe)
					m_OtherSafe.LoadNotif(cfg.Notifications.Other.PlayerInSafeZone);
				if (m_OtherPersist)
					m_OtherPersist.LoadNotif(cfg.Notifications.Other.BountyPersisted);
				if (m_OtherTeleport)
					m_OtherTeleport.LoadNotif(cfg.Notifications.Other.TeleportedOutOfTerritory);
				if (m_OtherPauseTerr)
					m_OtherPauseTerr.LoadNotif(cfg.Notifications.Other.BountyPausedInTerritory);
				if (m_OtherPauseSafe)
					m_OtherPauseSafe.LoadNotif(cfg.Notifications.Other.BountyPausedInSafeZone);
			}
		}
		if (cfg.Broadcasts)
		{
			if (m_BcPlaced)
				m_BcPlaced.LoadBroadcast(cfg.Broadcasts.PlacedBounty);
			if (m_BcRule)
				m_BcRule.LoadBroadcast(cfg.Broadcasts.RuleBreaker);
			if (m_BcExpired)
				m_BcExpired.LoadBroadcast(cfg.Broadcasts.Expired);
			if (m_BcWin)
				m_BcWin.LoadBroadcast(cfg.Broadcasts.Win);
			if (m_BcSuicide)
				m_BcSuicide.LoadBroadcast(cfg.Broadcasts.Suicide);
			if (m_BcLogout)
				m_BcLogout.LoadBroadcast(cfg.Broadcasts.Logout);
			if (m_BcWarning)
				m_BcWarning.LoadBroadcast(cfg.Broadcasts.Warning);
		}
	}

	void SaveToConfig(obfc_BountyConfig cfg)
	{
		if (!cfg)
			return;
		if (!cfg.Notifications)
			cfg.Notifications = new obfc_BountyNotificationConfig();
		if (!cfg.Notifications.PlacedBounty)
			cfg.Notifications.PlacedBounty = new obfc_BountyNotificationGroup();
		if (!cfg.Notifications.RuleBreaker)
			cfg.Notifications.RuleBreaker = new obfc_BountyRuleBreakerNotificationGroup();
		if (!cfg.Notifications.Other)
			cfg.Notifications.Other = new obfc_BountyOtherNotifications();
		if (!cfg.Broadcasts)
			cfg.Broadcasts = new obfc_BountyBroadcasts();

		if (m_PlacedHunted)
			m_PlacedHunted.SaveNotif(cfg.Notifications.PlacedBounty.Hunted);
		if (m_PlacedExpired)
			m_PlacedExpired.SaveNotif(cfg.Notifications.PlacedBounty.Expired);
		if (m_PlacedSurvival)
			m_PlacedSurvival.SaveNotif(cfg.Notifications.PlacedBounty.SurvivalReward);
		if (m_PlacedKilled)
			m_PlacedKilled.SaveNotif(cfg.Notifications.PlacedBounty.KilledReward);

		if (m_RuleHunted)
			m_RuleHunted.SaveNotif(cfg.Notifications.RuleBreaker.Hunted);
		if (m_RuleHitWarn)
			m_RuleHitWarn.SaveNotif(cfg.Notifications.RuleBreaker.HitWarning);
		if (m_RuleExpired)
			m_RuleExpired.SaveNotif(cfg.Notifications.RuleBreaker.Expired);
		if (m_RuleSurvival)
			m_RuleSurvival.SaveNotif(cfg.Notifications.RuleBreaker.SurvivalReward);
		if (m_RuleKilled)
			m_RuleKilled.SaveNotif(cfg.Notifications.RuleBreaker.KilledReward);

		if (m_OtherTokens)
			m_OtherTokens.SaveNotif(cfg.Notifications.Other.InsufficientTokens);
		if (m_OtherSkipNone)
			m_OtherSkipNone.SaveNotif(cfg.Notifications.Other.SkipBountyNoPlayers);
		if (m_OtherSkipOk)
			m_OtherSkipOk.SaveNotif(cfg.Notifications.Other.SkipBountySuccess);
		if (m_OtherSkipped)
			m_OtherSkipped.SaveNotif(cfg.Notifications.Other.BountySkipped);
		if (m_OtherHands)
			m_OtherHands.SaveNotif(cfg.Notifications.Other.RewardHandsNotFree);
		if (m_OtherCooldown)
			m_OtherCooldown.SaveNotif(cfg.Notifications.Other.PlayerOnCooldown);
		if (m_OtherSafe)
			m_OtherSafe.SaveNotif(cfg.Notifications.Other.PlayerInSafeZone);
		if (m_OtherPersist)
			m_OtherPersist.SaveNotif(cfg.Notifications.Other.BountyPersisted);
		if (m_OtherTeleport)
			m_OtherTeleport.SaveNotif(cfg.Notifications.Other.TeleportedOutOfTerritory);
		if (m_OtherPauseTerr)
			m_OtherPauseTerr.SaveNotif(cfg.Notifications.Other.BountyPausedInTerritory);
		if (m_OtherPauseSafe)
			m_OtherPauseSafe.SaveNotif(cfg.Notifications.Other.BountyPausedInSafeZone);

		if (m_BcPlaced)
			m_BcPlaced.SaveBroadcast(cfg.Broadcasts.PlacedBounty);
		if (m_BcRule)
			m_BcRule.SaveBroadcast(cfg.Broadcasts.RuleBreaker);
		if (m_BcExpired)
			m_BcExpired.SaveBroadcast(cfg.Broadcasts.Expired);
		if (m_BcWin)
			m_BcWin.SaveBroadcast(cfg.Broadcasts.Win);
		if (m_BcSuicide)
			m_BcSuicide.SaveBroadcast(cfg.Broadcasts.Suicide);
		if (m_BcLogout)
			m_BcLogout.SaveBroadcast(cfg.Broadcasts.Logout);
		if (m_BcWarning)
			m_BcWarning.SaveBroadcast(cfg.Broadcasts.Warning);
	}
}
