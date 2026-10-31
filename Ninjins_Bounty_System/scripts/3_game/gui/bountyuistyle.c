//! The look of Ninjins Core ("Black / Red" preset), which every Bounty layout carries as its defaults.
//! The mod does not need Core. With Core loaded, the admin's chosen colour preset replaces these values.
class obfc_BountyUiStyle
{
	static const int BTN_IDLE = 0xDC16161A;
	static const int BTN_HOVER = 0xEBB4202A;
	static const int BTN_ACTIVE = 0xFF1C1C20;
	static const int BTN_ACCENT = 0xF0C8232D;
	static const int BTN_ACCENT_HOVER = 0xFAE63741;
	static const int LABEL_NORMAL = 0xFFEBEBEE;
	static const int LIST_SURFACE = 0xFF23232A;
	static const int WINDOW_ROOT = 0xFC08080A;
	static const int ROW_PANEL = 0xF5060608;
	static const int SECTION_PANEL = 0xFA2A2A30;
	static const int SUBSECTION_PANEL = 0xF7202026;
	static const int SECTION_TEXT = 0xFFF8F2F4;
	static const int SUBSECTION_TEXT = 0xFFDCD7DA;
	static const int TITLE_BAR = 0xFF040406;

	private static Widget s_HoverWidget;
	private static int s_HoverRestoreColor;

	static int BtnIdle()
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		return NinjinsUpgraded_AdminColorStore.Read(NinjinsUpgraded_AdminColorId.BTN_IDLE);
		#else
		return BTN_IDLE;
		#endif
	}

	static int BtnHover()
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		return NinjinsUpgraded_AdminColorStore.Read(NinjinsUpgraded_AdminColorId.BTN_HOVER);
		#else
		return BTN_HOVER;
		#endif
	}

	static int BtnActive()
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		return NinjinsUpgraded_AdminColorStore.Read(NinjinsUpgraded_AdminColorId.BTN_ACTIVE);
		#else
		return BTN_ACTIVE;
		#endif
	}

	static int BtnAccent()
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		return NinjinsUpgraded_AdminColorStore.Read(NinjinsUpgraded_AdminColorId.BTN_ACCENT);
		#else
		return BTN_ACCENT;
		#endif
	}

	static int BtnAccentHover()
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		return NinjinsUpgraded_AdminColorStore.Read(NinjinsUpgraded_AdminColorId.BTN_ACCENT_HOVER);
		#else
		return BTN_ACCENT_HOVER;
		#endif
	}

	//! Repaints a freshly created layout from its default colours to the active Core preset.
	static void ApplyPreset(Widget root)
	{
		#ifdef Ninjins_Core
		NinjinsUpgraded_AdminColorStore.LoadIfNeeded();
		ApplyPresetToTree(root);
		#endif
	}

	#ifdef Ninjins_Core
	private static void ApplyPresetToTree(Widget widget)
	{
		Widget child;
		int presetId;
		if (!widget)
			return;
		presetId = PresetIdForColor(widget.GetColor());
		if (presetId >= 0)
			widget.SetColor(NinjinsUpgraded_AdminColorStore.Read(presetId));
		child = widget.GetChildren();
		while (child)
		{
			ApplyPresetToTree(child);
			child = child.GetSibling();
		}
	}

	private static int PresetIdForColor(int color)
	{
		if (SameColor(color, BTN_IDLE))
			return NinjinsUpgraded_AdminColorId.BTN_IDLE;
		if (SameColor(color, BTN_ACTIVE))
			return NinjinsUpgraded_AdminColorId.BTN_ACTIVE;
		if (SameColor(color, BTN_ACCENT))
			return NinjinsUpgraded_AdminColorId.BTN_ACCENT;
		if (SameColor(color, LABEL_NORMAL))
			return NinjinsUpgraded_AdminColorId.LABEL_NORMAL;
		if (SameColor(color, LIST_SURFACE))
			return NinjinsUpgraded_AdminColorId.LIST_SURFACE;
		if (SameColor(color, WINDOW_ROOT))
			return NinjinsUpgraded_AdminColorId.WINDOW_ROOT;
		if (SameColor(color, ROW_PANEL))
			return NinjinsUpgraded_AdminColorId.ROW_PANEL;
		if (SameColor(color, SECTION_PANEL))
			return NinjinsUpgraded_AdminColorId.SECTION_PANEL;
		if (SameColor(color, SUBSECTION_PANEL))
			return NinjinsUpgraded_AdminColorId.SUBSECTION_PANEL;
		if (SameColor(color, SECTION_TEXT))
			return NinjinsUpgraded_AdminColorId.SECTION_TEXT;
		if (SameColor(color, SUBSECTION_TEXT))
			return NinjinsUpgraded_AdminColorId.SUBSECTION_TEXT;
		if (SameColor(color, TITLE_BAR))
			return NinjinsUpgraded_AdminColorId.TITLE_BAR;
		return -1;
	}
	#endif

	//! A layout stores floats, so a channel can come back off by one.
	private static bool SameColor(int colorA, int colorB)
	{
		int shift;
		int channelA;
		int channelB;
		for (shift = 0; shift < 32; shift += 8)
		{
			channelA = (colorA >> shift) & 255;
			channelB = (colorB >> shift) & 255;
			if (Math.AbsInt(channelA - channelB) > 1)
				return false;
		}
		return true;
	}

	static void OnMouseEnter(Widget widget)
	{
		ButtonWidget button;
		int color;
		button = ButtonWidget.Cast(widget);
		if (!button || button.GetName() == "BttnClose" || button.GetName() == "BtnAdminClose")
			return;
		color = button.GetColor();
		s_HoverWidget = button;
		s_HoverRestoreColor = color;
		if (SameColor(color, BtnAccent()))
			button.SetColor(BtnAccentHover());
		else
			button.SetColor(BtnHover());
	}

	static void OnMouseLeave(Widget widget)
	{
		if (!widget || widget != s_HoverWidget)
			return;
		widget.SetColor(s_HoverRestoreColor);
		s_HoverWidget = null;
	}

	//! For buttons that change colour while they may be hovered, such as tabs.
	static void SetButtonColor(Widget button, int color)
	{
		if (!button)
			return;
		if (button == s_HoverWidget)
		{
			s_HoverRestoreColor = color;
			return;
		}
		button.SetColor(color);
	}
}
