class NinjinsBntyV3_AdmView
{
	protected ref NinjinsUpgraded_AdmDynForm m_Form;
	protected ref obfc_BountyConfig m_Cfg;

	protected ref NinjinsUpgraded_AdmRowBool m_EnableRow;
	protected ref NinjinsUpgraded_AdmRowText m_CooldownRow;
	protected ref NinjinsUpgraded_AdmRowInt m_MaxBountiedRow;
	protected ref NinjinsUpgraded_AdmRowInt m_MinOnlineRow;
	protected ref NinjinsUpgraded_AdmRowBool m_DisableSelfRow;
	protected ref NinjinsUpgraded_AdmRowInt m_SkipTokensRow;
	protected ref NinjinsUpgraded_AdmRowInt m_PlaceTokensRow;
	protected NinjinsUpgraded_AdmStrList m_TokenClassList;
	protected ref NinjinsUpgraded_AdmRowBool m_TeleportTerritoryRow;
	protected ref NinjinsUpgraded_AdmRowBool m_PauseTerritoryRow;
	protected ref NinjinsUpgraded_AdmRowText m_ResumeTerritoryDistRow;
	protected ref NinjinsUpgraded_AdmRowText m_PauseTerritoryIntervalRow;
	protected ref NinjinsUpgraded_AdmRowBool m_TeleportSafeRow;
	protected ref NinjinsUpgraded_AdmRowText m_TeleportSafeDistRow;
	protected ref NinjinsUpgraded_AdmRowBool m_PauseSafeRow;
	protected ref NinjinsUpgraded_AdmRowInt m_MinAliveRow;
	protected ref NinjinsUpgraded_AdmRowBool m_AutoPlaceRow;
	protected ref NinjinsUpgraded_AdmRowText m_AutoPlaceIntervalRow;
	protected ref NinjinsUpgraded_AdmRowBool m_PersistLogoutRow;
	protected ref NinjinsUpgraded_AdmRowBool m_DontSuicideRow;
	protected ref NinjinsUpgraded_AdmRowBool m_DontFriendlyRow;
	protected ref NinjinsUpgraded_AdmRowText m_WarningTimeRow;
	protected ref NinjinsUpgraded_AdmRowInt m_CostPerMinuteRow;
	protected ref NinjinsUpgraded_AdmRowInt m_MinMinutesRow;
	protected ref NinjinsUpgraded_AdmRowInt m_MaxMinutesRow;

	protected ref NinjinsUpgraded_AdmRowBool m_HitThresholdRow;
	protected ref NinjinsUpgraded_AdmRowBool m_PveToPvpRow;
	protected ref NinjinsUpgraded_AdmRowInt m_PveToPvpInstantRow;
	protected ref NinjinsUpgraded_AdmRowText m_RuleDurationRow;
	protected ref NinjinsUpgraded_AdmRowText m_HitWindowRow;
	protected ref NinjinsUpgraded_AdmRowInt m_HitWarnRow;
	protected ref NinjinsUpgraded_AdmRowInt m_HitBountyRow;
	protected ref NinjinsUpgraded_AdmRowBool m_ClearPendingRow;
	protected ref NinjinsUpgraded_AdmRowBool m_AllowPveKillRow;

	protected ref NinjinsUpgraded_AdmRowText m_PlacedDurationRow;
	protected ref NinjinsUpgraded_AdmRowBool m_SurvivalRewardRow;
	protected ref NinjinsUpgraded_AdmRowBool m_RuleBreakerRewardRow;

	protected ref NinjinsUpgraded_AdmRowBool m_MapDrawRow;
	protected ref NinjinsUpgraded_AdmRowText m_CircleRadiusRow;
	protected ref NinjinsUpgraded_AdmRowText m_CircleMinRadiusRow;
	protected ref NinjinsUpgraded_AdmRowBool m_CircleReduceRow;
	protected ref NinjinsUpgraded_AdmRowBool m_CircleIncreaseRow;
	protected ref NinjinsUpgraded_AdmRowColor m_CircleColorRow;
	protected ref NinjinsUpgraded_AdmRowInt m_CircleWidthRow;
	protected ref NinjinsUpgraded_AdmRowText m_MapUpdateRow;
	protected ref NinjinsUpgraded_AdmRowText m_MapRequestCdRow;
	protected ref NinjinsUpgraded_AdmRowText m_MapSyncRow;
	protected ref NinjinsUpgraded_AdmRowText m_MapSyncEmptyRow;
	protected ref NinjinsUpgraded_AdmRowText m_OffsetMinRow;
	protected ref NinjinsUpgraded_AdmRowText m_OffsetMaxRow;

	protected ref NinjinsUpgraded_AdmRowBool m_HardlineRow;
	protected ref NinjinsUpgraded_AdmRowInt m_HardlineAmountRow;
	protected ref NinjinsUpgraded_AdmRowText m_CountdownXRow;
	protected ref NinjinsUpgraded_AdmRowText m_CountdownYRow;
	protected ref NinjinsUpgraded_AdmRowText m_CountdownWRow;
	protected ref NinjinsUpgraded_AdmRowText m_CountdownHRow;
	protected ref NinjinsUpgraded_AdmRowColor m_CountdownBgRow;
	protected ref NinjinsUpgraded_AdmRowColor m_CountdownTextRow;
	protected NinjinsUpgraded_AdmStrList m_SuicidePhrasesList;
	protected ref NinjinsBntyV3_NotifUi m_NotifUi;

	protected NinjinsUpgraded_AdmStrList m_OnlinePlayersList;
	protected NinjinsUpgraded_AdmStrList m_BlacklistList;
	protected ref array<string> m_OnlinePlayerIds;
	protected ButtonWidget m_RefreshPlayersBtn;
	protected ButtonWidget m_PlaceBountyBtn;
	protected ButtonWidget m_PlaceRuleBreakerBtn;
	protected ButtonWidget m_ClearSelectedBountyBtn;
	protected ButtonWidget m_ClearMyBountyBtn;
	protected ButtonWidget m_ClearSelectedCooldownBtn;
	protected ButtonWidget m_ClearAllCooldownsBtn;
	protected ButtonWidget m_AddRewardBtn;
	protected ButtonWidget m_RemoveRewardBtn;
	protected ButtonWidget m_RefreshBlacklistBtn;
	protected ButtonWidget m_BlacklistAddBtn;
	protected ButtonWidget m_BlacklistRemoveBtn;
	protected ButtonWidget m_ReloadConfigsBtn;

	bool CreateIn(Widget parent)
	{
		if (!parent)
			return false;
		m_Form = new NinjinsUpgraded_AdmDynForm();
		if (!m_Form.CreateIn(parent))
			return false;
		m_Cfg = null;
		m_OnlinePlayerIds = new array<string>();
		LayoutFields();
		m_Form.SetFoldStoreScope("Bounty System", "Main");
		m_Form.RestoreStoredSectionFolds();
		AskAdminListsFromServer();
		return true;
	}

	void Destroy()
	{
		if (m_Form)
			m_Form.Destroy();
		m_Form = null;
		m_Cfg = null;
		m_EnableRow = null;
		m_CooldownRow = null;
		m_MaxBountiedRow = null;
		m_MinOnlineRow = null;
		m_DisableSelfRow = null;
		m_SkipTokensRow = null;
		m_PlaceTokensRow = null;
		m_TokenClassList = null;
		m_TeleportTerritoryRow = null;
		m_PauseTerritoryRow = null;
		m_ResumeTerritoryDistRow = null;
		m_PauseTerritoryIntervalRow = null;
		m_TeleportSafeRow = null;
		m_TeleportSafeDistRow = null;
		m_PauseSafeRow = null;
		m_MinAliveRow = null;
		m_AutoPlaceRow = null;
		m_AutoPlaceIntervalRow = null;
		m_PersistLogoutRow = null;
		m_DontSuicideRow = null;
		m_DontFriendlyRow = null;
		m_WarningTimeRow = null;
		m_CostPerMinuteRow = null;
		m_MinMinutesRow = null;
		m_MaxMinutesRow = null;
		m_HitThresholdRow = null;
		m_PveToPvpRow = null;
		m_PveToPvpInstantRow = null;
		m_RuleDurationRow = null;
		m_HitWindowRow = null;
		m_HitWarnRow = null;
		m_HitBountyRow = null;
		m_ClearPendingRow = null;
		m_AllowPveKillRow = null;
		m_PlacedDurationRow = null;
		m_SurvivalRewardRow = null;
		m_RuleBreakerRewardRow = null;
		m_MapDrawRow = null;
		m_CircleRadiusRow = null;
		m_CircleMinRadiusRow = null;
		m_CircleReduceRow = null;
		m_CircleIncreaseRow = null;
		m_CircleColorRow = null;
		m_CircleWidthRow = null;
		m_MapUpdateRow = null;
		m_MapRequestCdRow = null;
		m_MapSyncRow = null;
		m_MapSyncEmptyRow = null;
		m_OffsetMinRow = null;
		m_OffsetMaxRow = null;
		m_HardlineRow = null;
		m_HardlineAmountRow = null;
		m_CountdownXRow = null;
		m_CountdownYRow = null;
		m_CountdownWRow = null;
		m_CountdownHRow = null;
		m_CountdownBgRow = null;
		m_CountdownTextRow = null;
		m_SuicidePhrasesList = null;
		if (m_NotifUi)
			m_NotifUi.Destroy();
		m_NotifUi = null;
		m_OnlinePlayersList = null;
		m_BlacklistList = null;
		m_OnlinePlayerIds = null;
		m_RefreshPlayersBtn = null;
		m_PlaceBountyBtn = null;
		m_PlaceRuleBreakerBtn = null;
		m_ClearSelectedBountyBtn = null;
		m_ClearMyBountyBtn = null;
		m_ClearSelectedCooldownBtn = null;
		m_ClearAllCooldownsBtn = null;
		m_AddRewardBtn = null;
		m_RemoveRewardBtn = null;
		m_RefreshBlacklistBtn = null;
		m_BlacklistAddBtn = null;
		m_BlacklistRemoveBtn = null;
		m_ReloadConfigsBtn = null;
	}

	void PaintUiColors()
	{
		if (m_Form)
			m_Form.PaintUiColors();
		if (m_TokenClassList)
			m_TokenClassList.PaintUiColors();
		if (m_OnlinePlayersList)
			m_OnlinePlayersList.PaintUiColors();
		if (m_BlacklistList)
			m_BlacklistList.PaintUiColors();
		if (m_SuicidePhrasesList)
			m_SuicidePhrasesList.PaintUiColors();
	}

	void FoldAllPanels()
	{
		if (m_Form)
			m_Form.FoldAllPanels();
	}

	void ExpandAllPanels()
	{
		if (m_Form)
			m_Form.ExpandAllPanels();
	}

	bool OnClick(Widget w)
	{
		if (m_Form && m_Form.OnClick(w))
			return true;
		if (m_TokenClassList && m_TokenClassList.OnClick(w))
			return true;
		if (m_SuicidePhrasesList && m_SuicidePhrasesList.OnClick(w))
			return true;
		if (OnAdminActionClick(w))
			return true;
		return false;
	}

	void UpdateScrollLayout()
	{
		if (m_Form)
			m_Form.UpdateZoneEditorLayout(m_Form.GetRoot(), false);
	}

	protected string FloatText(float value)
	{
		return value.ToString();
	}

	protected float ReadFloat(NinjinsUpgraded_AdmRowText row, float fallback)
	{
		string textValue;
		if (!row)
			return fallback;
		textValue = row.ReadTextValue();
		if (textValue == "")
			return fallback;
		return textValue.ToFloat();
	}

	protected void LayoutFields()
	{
		m_Form.AddSectionTitle("Admin actions", false, "adminActions");
		m_OnlinePlayersList = m_Form.AddStrList("Online players");
		CompactSelectList(m_OnlinePlayersList);
		m_RefreshPlayersBtn = StretchActionButton(m_Form.AddAccentButton("Refresh players"));

		AddGroupLabel("/ add");
		m_PlaceBountyBtn = StretchActionButton(m_Form.AddAccentButton("Place bounty"));
		m_PlaceRuleBreakerBtn = StretchActionButton(m_Form.AddAccentButton("Place rule breaker"));
		m_AddRewardBtn = StretchActionButton(m_Form.AddAccentButton("Add reward point"));

		AddGroupLabel("/ remove");
		m_ClearSelectedBountyBtn = StretchActionButton(m_Form.AddAccentButton("Clear bounty"));
		m_ClearMyBountyBtn = StretchActionButton(m_Form.AddAccentButton("Clear my bounty"));
		m_RemoveRewardBtn = StretchActionButton(m_Form.AddAccentButton("Remove reward point"));

		AddGroupLabel("/ cooldown");
		m_ClearSelectedCooldownBtn = StretchActionButton(m_Form.AddAccentButton("Clear cooldown"));
		m_ClearAllCooldownsBtn = StretchActionButton(m_Form.AddAccentButton("Clear all cooldowns"));

		AddGroupLabel("/ blacklist");
		m_BlacklistList = m_Form.AddStrList("Blacklisted players");
		CompactSelectList(m_BlacklistList);
		m_RefreshBlacklistBtn = StretchActionButton(m_Form.AddAccentButton("Refresh blacklist"));
		m_BlacklistAddBtn = StretchActionButton(m_Form.AddAccentButton("Blacklist selected"));
		m_BlacklistRemoveBtn = StretchActionButton(m_Form.AddAccentButton("Remove from blacklist"));

		AddGroupLabel("/ configs");
		m_ReloadConfigsBtn = StretchActionButton(m_Form.AddAccentButton("Reload configs"));

		m_Form.AddSectionTitle("Core", false, "core");
		m_EnableRow = m_Form.AddBool("Enable bounty system", false);
		m_CooldownRow = m_Form.AddText("Bounty cooldown seconds", "3600");
		m_MaxBountiedRow = m_Form.AddInt("Max bountied players (-1 unlimited)", -1);
		m_MinOnlineRow = m_Form.AddInt("Min online players required", 1);
		m_DisableSelfRow = m_Form.AddBool("Disable self bounty", true);
		m_SkipTokensRow = m_Form.AddInt("Skip bounty tokens required", 10);
		m_PlaceTokensRow = m_Form.AddInt("Place bounty tokens required", 20);
		m_TokenClassList = m_Form.AddStrList("Bounty token class names");
		if (m_TokenClassList)
		{
			m_TokenClassList.SetClassBrowseEnabled(true);
			m_TokenClassList.ShowBrowseButton(true);
		}
		m_TeleportTerritoryRow = m_Form.AddBool("Teleport out of own territory", true);
		m_PauseTerritoryRow = m_Form.AddBool("Pause bounty in territory", true);
		m_ResumeTerritoryDistRow = m_Form.AddText("Resume distance from territory", "50");
		m_PauseTerritoryIntervalRow = m_Form.AddText("Paused bounty resume check interval", "5");
		m_TeleportSafeRow = m_Form.AddBool("Teleport out of safe zone", true);
		m_TeleportSafeDistRow = m_Form.AddText("Teleport out of safe zone distance", "150");
		m_PauseSafeRow = m_Form.AddBool("Pause bounty in safe zone", false);
		m_MinAliveRow = m_Form.AddInt("Minimum player lifetime seconds", 900);
		m_AutoPlaceRow = m_Form.AddBool("Enable automated bounty placement", false);
		m_AutoPlaceIntervalRow = m_Form.AddText("Automated placement interval seconds", "3600");
		m_PersistLogoutRow = m_Form.AddBool("Persistent bounty after logout", true);
		m_DontSuicideRow = m_Form.AddBool("Dont count suicide", true);
		m_DontFriendlyRow = m_Form.AddBool("Dont count friendly fire", true);
		m_WarningTimeRow = m_Form.AddText("Bounty warning time seconds", "0");
		m_CostPerMinuteRow = m_Form.AddInt("Request cost per minute", 0);
		m_MinMinutesRow = m_Form.AddInt("Request min minutes", 1);
		m_MaxMinutesRow = m_Form.AddInt("Request max minutes", 60);

		m_Form.AddSectionTitle("Rule breaker", false, "ruleBreaker");
		m_HitThresholdRow = m_Form.AddBool("Enable hit threshold", false);
		m_PveToPvpRow = m_Form.AddBool("Enable PvE to PvP rule breaker", true);
		m_PveToPvpInstantRow = m_Form.AddInt("PvE to PvP instant hits (0=threshold, 1=instant)", 0);
		m_RuleDurationRow = m_Form.AddText("Rule breaker duration seconds", "3600");
		m_HitWindowRow = m_Form.AddText("Hit threshold time window seconds", "10");
		m_HitWarnRow = m_Form.AddInt("Hit warning threshold", 10);
		m_HitBountyRow = m_Form.AddInt("Hit bounty threshold", 15);
		m_ClearPendingRow = m_Form.AddBool("Clear pending rewards on rule breaker", false);
		m_AllowPveKillRow = m_Form.AddBool("Allow PvE to PvE victim kill", false);
		m_HardlineRow = m_Form.AddBool("Expansion Hardline reputation decrease", false);
		m_HardlineAmountRow = m_Form.AddInt("Hardline reputation decrease amount", 0);

		m_Form.AddSectionTitle("Placed bounty / rewards", false, "placedReward");
		m_PlacedDurationRow = m_Form.AddText("Placed bounty duration seconds", "60");
		m_SurvivalRewardRow = m_Form.AddBool("Enable survival reward", true);
		m_RuleBreakerRewardRow = m_Form.AddBool("PvE rule breaker give rewards", false);

		m_Form.AddSectionTitle("Map", false, "map");
		m_MapDrawRow = m_Form.AddBool("Enable map drawing", true);
		m_CircleRadiusRow = m_Form.AddText("Circle radius", "100");
		m_CircleMinRadiusRow = m_Form.AddText("Circle min radius", "10");
		m_CircleReduceRow = m_Form.AddBool("Reduce radius over time", true);
		m_CircleIncreaseRow = m_Form.AddBool("Increase radius over time", false);
		m_CircleColorRow = m_Form.AddColor("Circle color", ARGB(255, 255, 0, 0));
		m_CircleWidthRow = m_Form.AddInt("Circle drawing width", 2);
		m_MapUpdateRow = m_Form.AddText("Map update interval seconds", "10");
		m_MapRequestCdRow = m_Form.AddText("Map request cooldown seconds", "10");
		m_MapSyncRow = m_Form.AddText("Map sync interval seconds", "10");
		m_MapSyncEmptyRow = m_Form.AddText("Map sync interval with no bounties", "10");
		m_OffsetMinRow = m_Form.AddText("Circle offset min multiplier", "0.1");
		m_OffsetMaxRow = m_Form.AddText("Circle offset max multiplier", "0.9");

		m_Form.AddSectionTitle("Countdown UI", false, "countdownUi");
		m_CountdownXRow = m_Form.AddText("Countdown position X (0=default)", "0");
		m_CountdownYRow = m_Form.AddText("Countdown position Y (0=default)", "0");
		m_CountdownWRow = m_Form.AddText("Countdown width (0=default)", "0");
		m_CountdownHRow = m_Form.AddText("Countdown height (0=default)", "0");
		m_CountdownBgRow = m_Form.AddColor("Countdown background color", 0);
		m_CountdownTextRow = m_Form.AddColor("Countdown text color", 0);

		m_Form.AddSectionTitle("Suicide phrases", false, "suicidePhrases");
		m_SuicidePhrasesList = m_Form.AddStrList("Suicide broadcast phrases");

		m_NotifUi = new NinjinsBntyV3_NotifUi();
		m_NotifUi.Layout(m_Form);
	}

	//! Selection-only list: hide add/remove editors and shrink empty bottom space.
	protected void CompactSelectList(NinjinsUpgraded_AdmStrList listRow)
	{
		Widget listRoot;
		Widget titleWidget;
		Widget listBorder;
		Widget addButton;
		Widget removeButton;
		Widget addEdit;
		Widget browseButton;
		Widget clearButton;

		if (!listRow)
			return;
		listRow.SetClassBrowseEnabled(false);
		listRow.ShowBrowseButton(false);
		listRoot = listRow.GetRoot();
		if (!listRoot)
			return;
		addButton = listRoot.FindAnyWidget("admin_strlist_add_btn");
		removeButton = listRoot.FindAnyWidget("admin_strlist_remove_btn");
		addEdit = listRoot.FindAnyWidget("admin_strlist_add_edit");
		browseButton = listRoot.FindAnyWidget("admin_strlist_browse_btn");
		clearButton = listRoot.FindAnyWidget("admin_strlist_add_clear_button");
		if (addButton)
			addButton.Show(false);
		if (removeButton)
			removeButton.Show(false);
		if (addEdit)
			addEdit.Show(false);
		if (browseButton)
			browseButton.Show(false);
		if (clearButton)
			clearButton.Show(false);
		titleWidget = listRoot.FindAnyWidget("admin_strlist_title");
		listBorder = listRoot.FindAnyWidget("admin_strlist_items_border");
		listRoot.SetSize(1, 118);
		if (titleWidget)
		{
			titleWidget.SetPos(0.02, 0.03);
			titleWidget.SetSize(0.96, 0.16);
		}
		if (listBorder)
		{
			listBorder.SetPos(0.02, 0.22);
			listBorder.SetSize(0.96, 0.72);
		}
	}

	//! Accent rows default to a right-side chip; stretch to full width and shorten row height.
	protected ButtonWidget StretchActionButton(ButtonWidget button)
	{
		Widget rowRoot;

		if (!button)
			return null;
		rowRoot = button.GetParent();
		button.SetPos(0.02, 0.08);
		button.SetSize(0.96, 0.84);
		if (rowRoot)
			rowRoot.SetSize(1, 28);
		return button;
	}

	//! Non-folding divider label inside the current Admin actions panel.
	protected void AddGroupLabel(string labelText)
	{
		Widget labelRoot;
		TextWidget labelTextWidget;

		if (!m_Form || !m_Form.GetRoot())
			return;
		labelRoot = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_V3_Bridge/gui/layouts/Admin/ninjins_bnty_v3_group_label.layout", m_Form.GetRoot());
		if (!labelRoot)
			return;
		labelTextWidget = TextWidget.Cast(labelRoot.FindAnyWidget("ninjins_bnty_v3_group_label_text"));
		if (labelTextWidget)
			labelTextWidget.SetText(labelText);
		m_Form.AddRowWidget(labelRoot);
	}

	protected string PlayerEntryDisplayName(string entry)
	{
		int separatorIndex;

		separatorIndex = entry.IndexOf("||");
		if (separatorIndex < 0)
			return entry;
		return entry.Substring(0, separatorIndex);
	}

	protected string PlayerEntryIdentifier(string entry)
	{
		int separatorIndex;

		separatorIndex = entry.IndexOf("||");
		if (separatorIndex < 0 || separatorIndex >= entry.Length() - 2)
			return entry;
		return entry.Substring(separatorIndex + 2, entry.Length() - (separatorIndex + 2));
	}

	void AskAdminListsFromServer()
	{
		AskOnlinePlayersFromServer();
		AskBlacklistFromServer();
	}

	void AskOnlinePlayersFromServer()
	{
		PlayerBase player;

		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestPlayers", new Param1<int>(0), true, player.GetIdentity());
	}

	void AskBlacklistFromServer()
	{
		PlayerBase player;

		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestBlacklist", new Param1<int>(0), true, player.GetIdentity());
	}

	void FillOnlinePlayers(array<string> players)
	{
		array<string> displayNames;
		string playerEntry;
		int entryIndex;

		if (!m_OnlinePlayersList)
			return;
		if (!m_OnlinePlayerIds)
			m_OnlinePlayerIds = new array<string>();
		m_OnlinePlayerIds.Clear();
		displayNames = new array<string>();
		if (players)
		{
			for (entryIndex = 0; entryIndex < players.Count(); entryIndex++)
			{
				playerEntry = players.Get(entryIndex);
				if (playerEntry == "")
					continue;
				m_OnlinePlayerIds.Insert(PlayerEntryIdentifier(playerEntry));
				displayNames.Insert(PlayerEntryDisplayName(playerEntry));
			}
		}
		m_OnlinePlayersList.LoadFromArray(displayNames);
	}

	void FillBlacklist(array<string> entries)
	{
		if (!m_BlacklistList)
			return;
		m_BlacklistList.LoadFromArray(entries);
	}

	protected string SelectedOnlinePlayerId()
	{
		int selectedRow;

		if (!m_OnlinePlayersList || !m_OnlinePlayerIds)
			return "";
		selectedRow = m_OnlinePlayersList.GetEffectiveSelectedRow();
		if (selectedRow < 0 || selectedRow >= m_OnlinePlayerIds.Count())
			return "";
		return m_OnlinePlayerIds.Get(selectedRow);
	}

	protected string SelectedBlacklistEntry()
	{
		array<string> entries;
		int selectedRow;

		if (!m_BlacklistList)
			return "";
		selectedRow = m_BlacklistList.GetEffectiveSelectedRow();
		if (selectedRow < 0)
			return "";
		entries = new array<string>();
		m_BlacklistList.CopyStringsToArray(entries);
		if (selectedRow >= entries.Count())
			return "";
		return entries.Get(selectedRow);
	}

	protected void SendAdminAction(string actionText)
	{
		PlayerBase player;

		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		if (actionText == "")
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>(actionText), true, player.GetIdentity());
	}

	protected void ShowNeedPlayerAlert()
	{
		NinjinsUpgraded_AdmAlert.ShowError("Bounty System", "Select a player first.");
	}

	protected void ShowNeedBlacklistAlert()
	{
		NinjinsUpgraded_AdmAlert.ShowError("Bounty System", "Select a blacklist entry first.");
	}

	protected bool OnAdminActionClick(Widget w)
	{
		string selectedPlayerId;
		string blacklistEntry;

		if (w == m_RefreshPlayersBtn)
		{
			AskOnlinePlayersFromServer();
			return true;
		}
		if (w == m_RefreshBlacklistBtn)
		{
			AskBlacklistFromServer();
			return true;
		}
		if (w == m_PlaceBountyBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("AddBountySelectedPlayer:" + selectedPlayerId);
			return true;
		}
		if (w == m_PlaceRuleBreakerBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("ApplyTestRuleBreakerBounty:" + selectedPlayerId);
			return true;
		}
		if (w == m_ClearSelectedBountyBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("ClearBountySelectedPlayer:" + selectedPlayerId);
			return true;
		}
		if (w == m_ClearMyBountyBtn)
		{
			SendAdminAction("ClearBounty");
			return true;
		}
		if (w == m_ClearSelectedCooldownBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("ClearPlayerCooldown:" + selectedPlayerId);
			return true;
		}
		if (w == m_ClearAllCooldownsBtn)
		{
			SendAdminAction("ClearAllCooldowns");
			return true;
		}
		if (w == m_AddRewardBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("AddRewardPoint:" + selectedPlayerId);
			return true;
		}
		if (w == m_RemoveRewardBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("RemoveRewardPoint:" + selectedPlayerId);
			return true;
		}
		if (w == m_BlacklistAddBtn)
		{
			selectedPlayerId = SelectedOnlinePlayerId();
			if (selectedPlayerId == "")
			{
				ShowNeedPlayerAlert();
				return true;
			}
			SendAdminAction("AddToBlacklist:" + selectedPlayerId);
			AskBlacklistFromServer();
			return true;
		}
		if (w == m_BlacklistRemoveBtn)
		{
			blacklistEntry = SelectedBlacklistEntry();
			if (blacklistEntry == "")
			{
				ShowNeedBlacklistAlert();
				return true;
			}
			SendAdminAction("RemoveFromBlacklist:" + blacklistEntry);
			AskBlacklistFromServer();
			return true;
		}
		if (w == m_ReloadConfigsBtn)
		{
			SendAdminAction("ReloadConfigs");
			return true;
		}
		return false;
	}

	void LoadFromConfig(obfc_BountyConfig cfg)
	{
		m_Cfg = cfg;
		if (!cfg || !cfg.Core || !cfg.RuleBreaker || !cfg.PlacedBounty || !cfg.Reward || !cfg.Map)
			return;

		if (m_EnableRow)
			m_EnableRow.SetChecked(cfg.Core.EnableBountySystem);
		if (m_CooldownRow)
			m_CooldownRow.SetTextValue(FloatText(cfg.Core.BountyCooldownSeconds));
		if (m_MaxBountiedRow)
			m_MaxBountiedRow.SetIntValue(cfg.Core.MaxBountiedPlayers);
		if (m_MinOnlineRow)
			m_MinOnlineRow.SetIntValue(cfg.Core.MinOnlinePlayersRequired);
		if (m_DisableSelfRow)
			m_DisableSelfRow.SetChecked(cfg.Core.DisableSelfBounty);
		if (m_SkipTokensRow)
			m_SkipTokensRow.SetIntValue(cfg.Core.SkipBountyTokenRequired);
		if (m_PlaceTokensRow)
			m_PlaceTokensRow.SetIntValue(cfg.Core.PlaceBountyTokenRequired);
		if (m_TokenClassList)
			m_TokenClassList.LoadFromArray(cfg.Core.BountyTokenClassNames);
		if (m_TeleportTerritoryRow)
			m_TeleportTerritoryRow.SetChecked(cfg.Core.obfm_TeleportOutOfOwnTerritory);
		if (m_PauseTerritoryRow)
			m_PauseTerritoryRow.SetChecked(cfg.Core.PauseBountyInTerritory);
		if (m_ResumeTerritoryDistRow)
			m_ResumeTerritoryDistRow.SetTextValue(FloatText(cfg.Core.ResumeBountyDistanceFromTerritory));
		if (m_PauseTerritoryIntervalRow)
			m_PauseTerritoryIntervalRow.SetTextValue(FloatText(cfg.Core.PausedBountyResumeCheckInterval));
		if (m_TeleportSafeRow)
			m_TeleportSafeRow.SetChecked(cfg.Core.obfm_TeleportOutOfSafeZone);
		if (m_TeleportSafeDistRow)
			m_TeleportSafeDistRow.SetTextValue(FloatText(cfg.Core.TeleportOutOfSafeZoneDistance));
		if (m_PauseSafeRow)
			m_PauseSafeRow.SetChecked(cfg.Core.PauseBountyInSafeZone);
		if (m_MinAliveRow)
			m_MinAliveRow.SetIntValue(cfg.Core.MinimumPlayerLifetimeSeconds);
		if (m_AutoPlaceRow)
			m_AutoPlaceRow.SetChecked(cfg.Core.EnableAutomatedBountyPlacement);
		if (m_AutoPlaceIntervalRow)
			m_AutoPlaceIntervalRow.SetTextValue(FloatText(cfg.Core.AutomatedBountyPlacementIntervalSeconds));
		if (m_PersistLogoutRow)
			m_PersistLogoutRow.SetChecked(cfg.Core.PersistentBountyAfterLogOut);
		if (m_DontSuicideRow)
			m_DontSuicideRow.SetChecked(cfg.Core.DontCountSuicide);
		if (m_DontFriendlyRow)
			m_DontFriendlyRow.SetChecked(cfg.Core.DontCountFriendlyFire);
		if (m_WarningTimeRow)
			m_WarningTimeRow.SetTextValue(FloatText(cfg.Core.BountyWarningTimeSeconds));
		if (m_CostPerMinuteRow)
			m_CostPerMinuteRow.SetIntValue(cfg.Core.BountyRequestCostPerMinute);
		if (m_MinMinutesRow)
			m_MinMinutesRow.SetIntValue(cfg.Core.BountyRequestMinMinutes);
		if (m_MaxMinutesRow)
			m_MaxMinutesRow.SetIntValue(cfg.Core.BountyRequestMaxMinutes);

		if (m_HitThresholdRow)
			m_HitThresholdRow.SetChecked(cfg.RuleBreaker.EnableRuleBreakerHitThreshold);
		if (m_PveToPvpRow)
			m_PveToPvpRow.SetChecked(cfg.RuleBreaker.EnablePvEToPvPRuleBreaker);
		if (m_PveToPvpInstantRow)
			m_PveToPvpInstantRow.SetIntValue(cfg.RuleBreaker.PvEToPvPInstantRuleBreakerHits);
		if (m_RuleDurationRow)
			m_RuleDurationRow.SetTextValue(FloatText(cfg.RuleBreaker.BountyRuleBreakerDurationSeconds));
		if (m_HitWindowRow)
			m_HitWindowRow.SetTextValue(FloatText(cfg.RuleBreaker.RuleBreakerHitThresholdTime));
		if (m_HitWarnRow)
			m_HitWarnRow.SetIntValue(cfg.RuleBreaker.RuleBreakerHitThresholdWarningHits);
		if (m_HitBountyRow)
			m_HitBountyRow.SetIntValue(cfg.RuleBreaker.RuleBreakerHitThresholdBountyHits);
		if (m_ClearPendingRow)
			m_ClearPendingRow.SetChecked(cfg.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty);
		if (m_AllowPveKillRow)
			m_AllowPveKillRow.SetChecked(cfg.RuleBreaker.AllowPvEToPvEVictimKill);
		if (m_HardlineRow)
			m_HardlineRow.SetChecked(cfg.RuleBreaker.Expansion_EnableHardlineReputationDecrease);
		if (m_HardlineAmountRow)
			m_HardlineAmountRow.SetIntValue(cfg.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);

		if (m_PlacedDurationRow)
			m_PlacedDurationRow.SetTextValue(FloatText(cfg.PlacedBounty.BountyDurationSeconds));
		if (m_SurvivalRewardRow)
			m_SurvivalRewardRow.SetChecked(cfg.Reward.EnableSurvivalReward);
		if (m_RuleBreakerRewardRow)
			m_RuleBreakerRewardRow.SetChecked(cfg.Reward.PvERuleBreakerGiveRewards);

		if (m_MapDrawRow)
			m_MapDrawRow.SetChecked(cfg.Map.BountyEnableMapDrawing);
		if (m_CircleRadiusRow)
			m_CircleRadiusRow.SetTextValue(FloatText(cfg.Map.BountyCircleRadius));
		if (m_CircleMinRadiusRow)
			m_CircleMinRadiusRow.SetTextValue(FloatText(cfg.Map.BountyCircleMinRadius));
		if (m_CircleReduceRow)
			m_CircleReduceRow.SetChecked(cfg.Map.BountyCircleReduceRadiusOverTime);
		if (m_CircleIncreaseRow)
			m_CircleIncreaseRow.SetChecked(cfg.Map.BountyCircleIncreaseRadiusOverTime);
		if (m_CircleColorRow)
			m_CircleColorRow.SetIntValue(cfg.Map.BountyCircleColor);
		if (m_CircleWidthRow)
			m_CircleWidthRow.SetIntValue(cfg.Map.BountyCircleDrawingWidth);
		if (m_MapUpdateRow)
			m_MapUpdateRow.SetTextValue(FloatText(cfg.Map.BountyMapUpdateIntervalSeconds));
		if (m_MapRequestCdRow)
			m_MapRequestCdRow.SetTextValue(FloatText(cfg.Map.BountyMapRequestCooldownSeconds));
		if (m_MapSyncRow)
			m_MapSyncRow.SetTextValue(FloatText(cfg.Map.BountyMapSyncIntervalSeconds));
		if (m_MapSyncEmptyRow)
			m_MapSyncEmptyRow.SetTextValue(FloatText(cfg.Map.BountyMapSyncIntervalNoBountiesSeconds));
		if (m_OffsetMinRow)
			m_OffsetMinRow.SetTextValue(FloatText(cfg.Map.BountyCircleOffsetMinMultiplier));
		if (m_OffsetMaxRow)
			m_OffsetMaxRow.SetTextValue(FloatText(cfg.Map.BountyCircleOffsetMaxMultiplier));

		if (cfg.UI)
		{
			if (m_CountdownXRow)
				m_CountdownXRow.SetTextValue(FloatText(cfg.UI.CountdownWidgetPositionX));
			if (m_CountdownYRow)
				m_CountdownYRow.SetTextValue(FloatText(cfg.UI.CountdownWidgetPositionY));
			if (m_CountdownWRow)
				m_CountdownWRow.SetTextValue(FloatText(cfg.UI.CountdownWidgetWidth));
			if (m_CountdownHRow)
				m_CountdownHRow.SetTextValue(FloatText(cfg.UI.CountdownWidgetHeight));
			if (m_CountdownBgRow)
				m_CountdownBgRow.SetIntValue(cfg.UI.CountdownWidgetBackgroundColor);
			if (m_CountdownTextRow)
				m_CountdownTextRow.SetIntValue(cfg.UI.CountdownWidgetTextColor);
		}
		if (m_SuicidePhrasesList && cfg.Core.SuicidePhrases)
			m_SuicidePhrasesList.LoadFromArray(cfg.Core.SuicidePhrases);
		if (m_NotifUi)
			m_NotifUi.LoadFromConfig(cfg);
	}

	obfc_BountyConfig ConfigForSaveFromUi()
	{
		obfc_BountyConfig cfg;
		array<string> tokenNames;
		array<string> suicidePhrases;

		cfg = new obfc_BountyConfig();
		if (m_Cfg)
		{
			if (m_Cfg.Notifications)
				cfg.Notifications = m_Cfg.Notifications;
			if (m_Cfg.Broadcasts)
				cfg.Broadcasts = m_Cfg.Broadcasts;
		}

		if (m_EnableRow)
			cfg.Core.EnableBountySystem = m_EnableRow.IsChecked();
		cfg.Core.BountyCooldownSeconds = ReadFloat(m_CooldownRow, 3600.0);
		if (m_MaxBountiedRow)
			cfg.Core.MaxBountiedPlayers = m_MaxBountiedRow.ReadIntValue();
		if (m_MinOnlineRow)
			cfg.Core.MinOnlinePlayersRequired = m_MinOnlineRow.ReadIntValue();
		if (m_DisableSelfRow)
			cfg.Core.DisableSelfBounty = m_DisableSelfRow.IsChecked();
		if (m_SkipTokensRow)
			cfg.Core.SkipBountyTokenRequired = m_SkipTokensRow.ReadIntValue();
		if (m_PlaceTokensRow)
			cfg.Core.PlaceBountyTokenRequired = m_PlaceTokensRow.ReadIntValue();
		tokenNames = new array<string>();
		if (m_TokenClassList)
			m_TokenClassList.CopyStringsToArray(tokenNames);
		cfg.Core.BountyTokenClassNames = tokenNames;
		if (m_TeleportTerritoryRow)
			cfg.Core.obfm_TeleportOutOfOwnTerritory = m_TeleportTerritoryRow.IsChecked();
		if (m_PauseTerritoryRow)
			cfg.Core.PauseBountyInTerritory = m_PauseTerritoryRow.IsChecked();
		cfg.Core.ResumeBountyDistanceFromTerritory = ReadFloat(m_ResumeTerritoryDistRow, 50.0);
		cfg.Core.PausedBountyResumeCheckInterval = ReadFloat(m_PauseTerritoryIntervalRow, 5.0);
		if (m_TeleportSafeRow)
			cfg.Core.obfm_TeleportOutOfSafeZone = m_TeleportSafeRow.IsChecked();
		cfg.Core.TeleportOutOfSafeZoneDistance = ReadFloat(m_TeleportSafeDistRow, 150.0);
		if (m_PauseSafeRow)
			cfg.Core.PauseBountyInSafeZone = m_PauseSafeRow.IsChecked();
		if (m_MinAliveRow)
			cfg.Core.MinimumPlayerLifetimeSeconds = m_MinAliveRow.ReadIntValue();
		if (m_AutoPlaceRow)
			cfg.Core.EnableAutomatedBountyPlacement = m_AutoPlaceRow.IsChecked();
		cfg.Core.AutomatedBountyPlacementIntervalSeconds = ReadFloat(m_AutoPlaceIntervalRow, 3600.0);
		if (m_PersistLogoutRow)
			cfg.Core.PersistentBountyAfterLogOut = m_PersistLogoutRow.IsChecked();
		if (m_DontSuicideRow)
			cfg.Core.DontCountSuicide = m_DontSuicideRow.IsChecked();
		if (m_DontFriendlyRow)
			cfg.Core.DontCountFriendlyFire = m_DontFriendlyRow.IsChecked();
		cfg.Core.BountyWarningTimeSeconds = ReadFloat(m_WarningTimeRow, 0.0);
		if (m_CostPerMinuteRow)
			cfg.Core.BountyRequestCostPerMinute = m_CostPerMinuteRow.ReadIntValue();
		if (m_MinMinutesRow)
			cfg.Core.BountyRequestMinMinutes = m_MinMinutesRow.ReadIntValue();
		if (m_MaxMinutesRow)
			cfg.Core.BountyRequestMaxMinutes = m_MaxMinutesRow.ReadIntValue();

		if (m_HitThresholdRow)
			cfg.RuleBreaker.EnableRuleBreakerHitThreshold = m_HitThresholdRow.IsChecked();
		if (m_PveToPvpRow)
			cfg.RuleBreaker.EnablePvEToPvPRuleBreaker = m_PveToPvpRow.IsChecked();
		if (m_PveToPvpInstantRow)
			cfg.RuleBreaker.PvEToPvPInstantRuleBreakerHits = m_PveToPvpInstantRow.ReadIntValue();
		cfg.RuleBreaker.BountyRuleBreakerDurationSeconds = ReadFloat(m_RuleDurationRow, 3600.0);
		cfg.RuleBreaker.RuleBreakerHitThresholdTime = ReadFloat(m_HitWindowRow, 10.0);
		if (m_HitWarnRow)
			cfg.RuleBreaker.RuleBreakerHitThresholdWarningHits = m_HitWarnRow.ReadIntValue();
		if (m_HitBountyRow)
			cfg.RuleBreaker.RuleBreakerHitThresholdBountyHits = m_HitBountyRow.ReadIntValue();
		if (m_ClearPendingRow)
			cfg.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = m_ClearPendingRow.IsChecked();
		if (m_AllowPveKillRow)
			cfg.RuleBreaker.AllowPvEToPvEVictimKill = m_AllowPveKillRow.IsChecked();
		if (m_HardlineRow)
			cfg.RuleBreaker.Expansion_EnableHardlineReputationDecrease = m_HardlineRow.IsChecked();
		if (m_HardlineAmountRow)
			cfg.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = m_HardlineAmountRow.ReadIntValue();

		cfg.PlacedBounty.BountyDurationSeconds = ReadFloat(m_PlacedDurationRow, 60.0);
		if (m_SurvivalRewardRow)
			cfg.Reward.EnableSurvivalReward = m_SurvivalRewardRow.IsChecked();
		if (m_RuleBreakerRewardRow)
			cfg.Reward.PvERuleBreakerGiveRewards = m_RuleBreakerRewardRow.IsChecked();

		if (m_MapDrawRow)
			cfg.Map.BountyEnableMapDrawing = m_MapDrawRow.IsChecked();
		cfg.Map.BountyCircleRadius = ReadFloat(m_CircleRadiusRow, 100.0);
		cfg.Map.BountyCircleMinRadius = ReadFloat(m_CircleMinRadiusRow, 10.0);
		if (m_CircleReduceRow)
			cfg.Map.BountyCircleReduceRadiusOverTime = m_CircleReduceRow.IsChecked();
		if (m_CircleIncreaseRow)
			cfg.Map.BountyCircleIncreaseRadiusOverTime = m_CircleIncreaseRow.IsChecked();
		if (m_CircleColorRow)
			cfg.Map.BountyCircleColor = m_CircleColorRow.ReadIntValue();
		if (m_CircleWidthRow)
			cfg.Map.BountyCircleDrawingWidth = m_CircleWidthRow.ReadIntValue();
		cfg.Map.BountyMapUpdateIntervalSeconds = ReadFloat(m_MapUpdateRow, 10.0);
		cfg.Map.BountyMapRequestCooldownSeconds = ReadFloat(m_MapRequestCdRow, 10.0);
		cfg.Map.BountyMapSyncIntervalSeconds = ReadFloat(m_MapSyncRow, 10.0);
		cfg.Map.BountyMapSyncIntervalNoBountiesSeconds = ReadFloat(m_MapSyncEmptyRow, 10.0);
		cfg.Map.BountyCircleOffsetMinMultiplier = ReadFloat(m_OffsetMinRow, 0.1);
		cfg.Map.BountyCircleOffsetMaxMultiplier = ReadFloat(m_OffsetMaxRow, 0.9);

		if (!cfg.UI)
			cfg.UI = new obfc_BountyUISettings();
		cfg.UI.CountdownWidgetPositionX = ReadFloat(m_CountdownXRow, 0.0);
		cfg.UI.CountdownWidgetPositionY = ReadFloat(m_CountdownYRow, 0.0);
		cfg.UI.CountdownWidgetWidth = ReadFloat(m_CountdownWRow, 0.0);
		cfg.UI.CountdownWidgetHeight = ReadFloat(m_CountdownHRow, 0.0);
		if (m_CountdownBgRow)
			cfg.UI.CountdownWidgetBackgroundColor = m_CountdownBgRow.ReadIntValue();
		if (m_CountdownTextRow)
			cfg.UI.CountdownWidgetTextColor = m_CountdownTextRow.ReadIntValue();

		suicidePhrases = new array<string>();
		if (m_SuicidePhrasesList)
			m_SuicidePhrasesList.CopyStringsToArray(suicidePhrases);
		cfg.Core.SuicidePhrases = suicidePhrases;

		if (m_NotifUi)
			m_NotifUi.SaveToConfig(cfg);

		m_Cfg = cfg;
		return cfg;
	}
}

class NinjinsBntyV3_AdmMod: NinjinsUpgraded_AdminModBase
{
	override string GetLayoutRoot()
	{
		return "Ninjins_Bounty_V3_Bridge/gui/layouts/Admin/ninjins_bounty_v3_bridge_form.layout";
	}

	override string GetTitle()
	{
		return "Bounty System";
	}

	override string GetIconName()
	{
		return "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
	}

	override bool ImageIsIcon()
	{
		return true;
	}

	override bool ImageHasPath()
	{
		return true;
	}

	override string GetMenuGroup()
	{
		return "Server";
	}

	void RequestConfigFromServer()
	{
		GetRPCManager().SendRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_AskCfg", null, true, null);
	}
}

class NinjinsBntyV3_AdmForm: NinjinsUpgraded_AdminForm
{
	protected ref NinjinsBntyV3_AdmView m_View;
	protected Widget m_MainPanel;
	protected ButtonWidget m_SaveButton;
	protected ButtonWidget m_ReloadButton;
	protected ButtonWidget m_ViewRawButton;
	protected ImageWidget m_SaveButtonIcon;
	protected ImageWidget m_ReloadButtonIcon;
	protected ImageWidget m_ViewRawButtonIcon;
	protected string m_RawBody;
	protected ref NinjinsUpgraded_RawWnd m_RawWnd;
	protected bool m_AwaitingReload;

	override bool SetModule(NinjinsUpgraded_AdminModBase module)
	{
		NinjinsBntyV3_AdmMod bountyModule;

		bountyModule = NinjinsBntyV3_AdmMod.Cast(module);
		if (!bountyModule)
			return false;
		m_Module = bountyModule;
		return true;
	}

	override void OnInit()
	{
		NinjinsBntyV3_AdmMod bountyModule;

		m_AwaitingReload = false;
		m_RawBody = "";
		m_RawWnd = null;
		m_MainPanel = m_LayoutRoot.FindAnyWidget("main_panel");
		Class.CastTo(m_SaveButton, m_LayoutRoot.FindAnyWidget("save_button"));
		Class.CastTo(m_ReloadButton, m_LayoutRoot.FindAnyWidget("reload_button"));
		Class.CastTo(m_ViewRawButton, m_LayoutRoot.FindAnyWidget("view_raw_button"));
		Class.CastTo(m_SaveButtonIcon, m_LayoutRoot.FindAnyWidget("save_button_icon"));
		Class.CastTo(m_ReloadButtonIcon, m_LayoutRoot.FindAnyWidget("reload_button_icon"));
		Class.CastTo(m_ViewRawButtonIcon, m_LayoutRoot.FindAnyWidget("view_raw_button_icon"));
		NinjinsUpgraded_IcoBrowse.LoadToolbarIcon(m_SaveButtonIcon, "save");
		NinjinsUpgraded_IcoBrowse.LoadToolbarIcon(m_ReloadButtonIcon, "refresh");
		NinjinsUpgraded_IcoBrowse.LoadToolbarIcon(m_ViewRawButtonIcon, "raw");
		m_View = new NinjinsBntyV3_AdmView();
		if (m_MainPanel && m_View)
			m_View.CreateIn(m_MainPanel);
		bountyModule = NinjinsBntyV3_AdmMod.Cast(m_Module);
		if (bountyModule)
			bountyModule.RequestConfigFromServer();
	}

	override void OnShow()
	{
		ScheduleScrollUpdate();
		if (m_View)
			m_View.AskAdminListsFromServer();
	}

	void FillOnlinePlayersFromServer(array<string> players)
	{
		if (m_View)
			m_View.FillOnlinePlayers(players);
	}

	void FillBlacklistFromServer(array<string> entries)
	{
		if (m_View)
			m_View.FillBlacklist(entries);
	}

	override void OnHide()
	{
		super.OnHide();
		NinjinsUpgraded_RawWndOps.CloseIfOpen(m_RawWnd);
		m_RawWnd = null;
		if (m_View)
			m_View.Destroy();
		m_View = null;
	}

	override void PaintUiColors()
	{
		if (m_LayoutRoot)
			m_LayoutRoot.SetColor(NinjinsUpgraded_UiPal.WindowRoot());
		if (m_SaveButton)
			m_SaveButton.SetColor(NinjinsUpgraded_UiPal.BtnIdle());
		if (m_ReloadButton)
			m_ReloadButton.SetColor(NinjinsUpgraded_UiPal.BtnIdle());
		if (m_ViewRawButton)
			m_ViewRawButton.SetColor(NinjinsUpgraded_UiPal.BtnIdle());
		if (m_View)
			m_View.PaintUiColors();
	}

	protected void ScheduleScrollUpdate()
	{
		if (NinjinsUpgraded_AdminStatics.IsClientUiShuttingDown())
			return;
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateScrollLayout);
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateScrollLayout, 50, false);
	}

	protected void UpdateScrollLayout()
	{
		if (NinjinsUpgraded_AdminStatics.IsClientUiShuttingDown())
			return;
		if (!m_LayoutRoot || m_LayoutRoot.ToString() == "INVALID")
			return;
		if (m_View)
			m_View.UpdateScrollLayout();
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_SaveButton)
		{
			SendSaveToServer();
			return true;
		}
		if (w == m_ReloadButton)
		{
			SendReloadToServer();
			return true;
		}
		if (w == m_ViewRawButton)
		{
			OpenRaw();
			return true;
		}
		if (m_View && m_View.OnClick(w))
			return true;
		return false;
	}

	override bool HasPanelFoldButtons()
	{
		return true;
	}

	override void FoldAllPanels()
	{
		if (m_View)
			m_View.FoldAllPanels();
	}

	override void ExpandAllPanels()
	{
		if (m_View)
			m_View.ExpandAllPanels();
	}

	protected void SendSaveToServer()
	{
		obfc_BountyConfig cfg;
		Param1<ref obfc_BountyConfig> payload;

		if (!m_View)
			return;
		cfg = m_View.ConfigForSaveFromUi();
		if (!cfg)
			return;
		m_RawBody = MakeRawBody(cfg);
		payload = new Param1<ref obfc_BountyConfig>(cfg);
		GetRPCManager().SendRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_SaveCfg", payload, true, null);
	}

	protected void SendReloadToServer()
	{
		m_AwaitingReload = true;
		GetRPCManager().SendRPC(NinjinsBntyV3_Const.RPC_SPACE, "NinjinsBntyV3_ReloadCfg", null, true, null);
	}

	void LoadConfigFromServer(obfc_BountyConfig cfg)
	{
		if (m_View)
			m_View.LoadFromConfig(cfg);
		m_RawBody = MakeRawBody(cfg);
		ScheduleScrollUpdate();
		if (m_AwaitingReload)
		{
			m_AwaitingReload = false;
			NinjinsUpgraded_AdmAlert.ShowSuccess("Bounty System", "Settings reloaded from server");
		}
	}

	void OnSaveResultFromServer(bool saved)
	{
		if (saved)
		{
			NinjinsUpgraded_AdmAlert.ShowSuccess("Bounty System", "Settings saved.");
			return;
		}
		NinjinsUpgraded_AdmAlert.ShowError("Bounty System", "Settings save failed.");
	}

	protected string MakeRawBody(obfc_BountyConfig cfg)
	{
		string body;
		string error;

		body = "";
		if (!cfg)
			return body;
		if (!JsonFileLoader<obfc_BountyConfig>.MakeData(cfg, body, error, true))
			return "";
		return body;
	}

	protected void OpenRaw()
	{
		string rawBody;

		rawBody = m_RawBody;
		if (rawBody == "")
			rawBody = "{\n\t\"note\": \"No config received from server yet.\"\n}";
		NinjinsUpgraded_RawWndOps.CloseIfOpen(m_RawWnd);
		m_RawWnd = NinjinsUpgraded_RawWndOps.OpenReadOnly("Bounty System - Raw JSON", rawBody, GetOwnerWindow());
	}
}
