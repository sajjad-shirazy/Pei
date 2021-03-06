#include <Pei.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Pei.lib")
#pragma comment(lib, "winmm.lib")

using namespace Pei::Graphic;
using namespace Pei::Utility;

int main()
{
	SPLoopManager loopman;
	loopman.AllowSleep(false);

	
	SPWindow win(0,"; )");
	SPRenderer* renderer = new SPRenderer(win.GetHandle());
	//renderer->Fullscreen();

	renderer->SetLightEnable(true);
	renderer->SetAlphaTestEnable(false);
	renderer->SetAlphaBlendEnable(false);
	renderer->SetTextureSamplerEnabled(true);
	//renderer->SetFillMode(SPRenderer::FillMode_Wireframe);
	renderer->GetCamera()->Walk(-1450);
	renderer->GetCamera()->Fly(600);
	renderer->GetCamera()->Pitch(0.2f);
	//renderer->GetCamera()->SetCameraSize(1366,768);

	//مدیر منابع اگر منبع درخواستی قبلا بارگزاری شده باشد اشاره گر به آن را بر می گرداند
	//در غیر این صورت آن را بارگزاری می کند و اشاره گر منبع جدید را باز می گرداند.
	SPMesh* teapot = Pei::SPResourceManager::GetMesh("Object3D.X");
	teapot->SetCurrentSubsetIndex(0);

	SPRenderingParameters rp;
	//rp.position.z += 2500;
	rp.Transform();

	SPColor color(0,0,0);

	while(!win.IsWindowClosed())
	{		
		loopman.BeginLoop();
		SPWindow::ProcessMessages();
		renderer->StartRendering();
		renderer->ClearBackBuffer(&color);		
		renderer->GetCamera()->Walk(0.2f);

		rp.rotation.y += 0.02f;
		rp.Transform();
		teapot->Render(&rp);

		renderer->StopRendering();
		loopman.EndLoop();
	}
	Pei::SPResourceManager::RemoveResources(0);
	return 0;
}