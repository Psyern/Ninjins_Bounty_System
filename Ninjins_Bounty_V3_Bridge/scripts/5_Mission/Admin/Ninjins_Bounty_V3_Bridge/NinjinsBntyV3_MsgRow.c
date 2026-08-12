//! One Enabled/Title/Message/IconPath block in the bounty admin sidebar (v2 parity).
class NinjinsBntyV3_MsgRow
{
	ref NinjinsUpgraded_AdmRowBool m_EnabledRow;
	ref NinjinsUpgraded_AdmRowText m_TitleRow;
	ref NinjinsUpgraded_AdmRowText m_MessageRow;
	ref NinjinsUpgraded_AdmRowText m_IconRow;

	void Layout(NinjinsUpgraded_AdmDynForm form, string labelPrefix)
	{
		if (!form)
			return;
		m_EnabledRow = form.AddBool(labelPrefix + " enabled", true);
		m_TitleRow = form.AddText(labelPrefix + " title", "");
		m_MessageRow = form.AddText(labelPrefix + " message", "");
		m_IconRow = form.AddText(labelPrefix + " icon path", "");
	}

	void Destroy()
	{
		m_EnabledRow = null;
		m_TitleRow = null;
		m_MessageRow = null;
		m_IconRow = null;
	}

	void LoadNotif(obfc_BountyNotificationEntry entry)
	{
		if (!entry)
			return;
		if (m_EnabledRow)
			m_EnabledRow.SetChecked(entry.Enabled);
		if (m_TitleRow)
			m_TitleRow.SetTextValue(entry.Title);
		if (m_MessageRow)
			m_MessageRow.SetTextValue(entry.Message);
		if (m_IconRow)
			m_IconRow.SetTextValue(entry.IconPath);
	}

	void SaveNotif(obfc_BountyNotificationEntry entry)
	{
		if (!entry)
			return;
		if (m_EnabledRow)
			entry.Enabled = m_EnabledRow.IsChecked();
		if (m_TitleRow)
			entry.Title = m_TitleRow.ReadTextValue();
		if (m_MessageRow)
			entry.Message = m_MessageRow.ReadTextValue();
		if (m_IconRow)
			entry.IconPath = m_IconRow.ReadTextValue();
	}

	void LoadBroadcast(obfc_BountyBroadcastEntry entry)
	{
		if (!entry)
			return;
		if (m_EnabledRow)
			m_EnabledRow.SetChecked(entry.Enabled);
		if (m_TitleRow)
			m_TitleRow.SetTextValue(entry.Title);
		if (m_MessageRow)
			m_MessageRow.SetTextValue(entry.Message);
		if (m_IconRow)
			m_IconRow.SetTextValue(entry.IconPath);
	}

	void SaveBroadcast(obfc_BountyBroadcastEntry entry)
	{
		if (!entry)
			return;
		if (m_EnabledRow)
			entry.Enabled = m_EnabledRow.IsChecked();
		if (m_TitleRow)
			entry.Title = m_TitleRow.ReadTextValue();
		if (m_MessageRow)
			entry.Message = m_MessageRow.ReadTextValue();
		if (m_IconRow)
			entry.IconPath = m_IconRow.ReadTextValue();
	}
}
