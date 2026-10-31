//! Ninjins Core window behaviour for a panel with a title bar: drag by the title bar, minimize to the title bar.
//! The panel must use relative position and size and be vertically centered.
class obfc_BountyUiWindow
{
	private Widget obfv_m_Window;
	private Widget obfv_m_TitleBar;
	private ButtonWidget obfv_m_MinimizeButton;
	private ref array<Widget> obfv_m_HiddenWidgets;
	private float obfv_m_DirectionX;
	private bool obfv_m_IsDragging;
	private int obfv_m_DragMouseX;
	private int obfv_m_DragMouseY;
	private float obfv_m_DragPosX;
	private float obfv_m_DragPosY;
	private float obfv_m_RestoreHeight;

	//! directionX is 1 for a left aligned panel and -1 for a right aligned one.
	void obfc_BountyUiWindow(Widget window, Widget titleBar, ButtonWidget minimizeButton, float directionX)
	{
		obfv_m_Window = window;
		obfv_m_TitleBar = titleBar;
		obfv_m_MinimizeButton = minimizeButton;
		obfv_m_DirectionX = directionX;
		obfv_m_HiddenWidgets = new array<Widget>;
	}

	bool OnMouseButtonDown(Widget widget, int button)
	{
		if (!obfv_m_Window || widget != obfv_m_TitleBar || button != MouseState.LEFT)
			return false;
		GetMousePos(obfv_m_DragMouseX, obfv_m_DragMouseY);
		obfv_m_Window.GetPos(obfv_m_DragPosX, obfv_m_DragPosY);
		obfv_m_IsDragging = true;
		return true;
	}

	bool OnClick(Widget widget)
	{
		if (!obfv_m_Window || !widget || widget != obfv_m_MinimizeButton)
			return false;
		if (obfv_m_RestoreHeight > 0)
			Restore();
		else
			Minimize();
		return true;
	}

	void Update()
	{
		int mouseX;
		int mouseY;
		int screenX;
		int screenY;
		float parentWidth;
		float parentHeight;
		if (!obfv_m_IsDragging || !obfv_m_Window)
			return;
		if (!(GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK))
		{
			obfv_m_IsDragging = false;
			return;
		}
		obfv_m_Window.GetParent().GetScreenSize(parentWidth, parentHeight);
		if (parentWidth <= 0 || parentHeight <= 0)
			return;
		GetMousePos(mouseX, mouseY);
		GetScreenSize(screenX, screenY);
		// The grabbed point stays on screen, so the title bar can always be reached again.
		mouseX = Math.Clamp(mouseX, 0, screenX - 1);
		mouseY = Math.Clamp(mouseY, 0, screenY - 1);
		obfv_m_Window.SetPos(obfv_m_DragPosX + obfv_m_DirectionX * (mouseX - obfv_m_DragMouseX) / parentWidth, obfv_m_DragPosY + (mouseY - obfv_m_DragMouseY) / parentHeight);
	}

	private void Minimize()
	{
		float width;
		float height;
		float posX;
		float posY;
		float parentWidth;
		float parentHeight;
		float titleWidth;
		float titleHeight;
		float newHeight;
		Widget child;
		obfv_m_Window.GetSize(width, height);
		obfv_m_Window.GetPos(posX, posY);
		obfv_m_Window.GetParent().GetScreenSize(parentWidth, parentHeight);
		obfv_m_TitleBar.GetScreenSize(titleWidth, titleHeight);
		if (parentHeight <= 0)
			return;
		child = obfv_m_Window.GetChildren();
		while (child)
		{
			if (child != obfv_m_TitleBar && child.IsVisible())
			{
				obfv_m_HiddenWidgets.Insert(child);
				child.Show(false);
			}
			child = child.GetSibling();
		}
		newHeight = titleHeight / parentHeight;
		obfv_m_RestoreHeight = height;
		obfv_m_Window.SetSize(width, newHeight);
		// The panel is vertically centered, so its position moves to keep the title bar in place.
		obfv_m_Window.SetPos(posX, posY - (height - newHeight) * 0.5);
	}

	private void Restore()
	{
		float width;
		float height;
		float posX;
		float posY;
		int index;
		obfv_m_Window.GetSize(width, height);
		obfv_m_Window.GetPos(posX, posY);
		obfv_m_Window.SetSize(width, obfv_m_RestoreHeight);
		obfv_m_Window.SetPos(posX, posY + (obfv_m_RestoreHeight - height) * 0.5);
		for (index = 0; index < obfv_m_HiddenWidgets.Count(); index++)
		{
			if (obfv_m_HiddenWidgets[index])
				obfv_m_HiddenWidgets[index].Show(true);
		}
		obfv_m_HiddenWidgets.Clear();
		obfv_m_RestoreHeight = 0;
	}
}
