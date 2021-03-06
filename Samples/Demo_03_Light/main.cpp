#include <Pei.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Pei_d.lib")
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

	//renderer->SetLightEnable(true);
	renderer->SetAlphaTestEnable(false);
	renderer->SetAlphaBlendEnable(false);
	renderer->SetTextureSamplerEnabled(true);
	//renderer->SetFillMode(SPRenderer::FillMode_Wireframe);
	renderer->GetCamera()->Walk(-25);
	renderer->GetCamera()->Fly(5);
	//renderer->GetCamera()->Pitch(0.2f);
	//renderer->GetCamera()->SetCameraSize(1366,768);

	//مدیر منابع اگر منبع درخواستی قبلا بارگزاری شده باشد اشاره گر به آن را بر می گرداند
	//در غیر این صورت آن را بارگزاری می کند و اشاره گر منبع جدید را باز می گرداند.
	SPMesh* teapot = Pei::SPResourceManager::GetMesh("wall_with_pillars.x");
	teapot->SetCurrentSubsetIndex(-1);

	SPRenderingParameters rp;
	rp.position.x -= 3;
	rp.rotation.y += Math::PI/11.0f;
	rp.Transform();

	SPColor color(0,0,0);

	//دایرکت تری دی 8 تا اسلات نور داره که با لایت آی دی توی کلاس لایت تعین می شه این لایت برای کدوم اسلاته
	// خود موتور با متود لایت اینیبل اسلات صفر رو برای نور کلی صحنه ست می کنه
	SPLight* spotLight = new SPLight(1,D3DLIGHT_SPOT,SPVector3(0,0,0),SPVector3(0,1,0),40);
	/*SPLight* pointLight1 = new SPLight(2,D3DLIGHT_POINT,SPVector3(40,10,0),SPVector3(0,1,0),42);
	pointLight1->heart.Diffuse.g = pointLight1->heart.Ambient.g = 0.0f;
	pointLight1->heart.Diffuse.b = pointLight1->heart.Ambient.b = 0.0f;
	pointLight1->Register();
	SPLight* pointLight2 = new SPLight(3,D3DLIGHT_POINT,SPVector3(-40,10,0),SPVector3(0,1,0),42);
	pointLight2->heart.Diffuse.g = pointLight2->heart.Ambient.g = 0.0f;
	pointLight2->heart.Diffuse.b = pointLight2->heart.Ambient.r = 0.0f;
	pointLight2->Register();*/

	while(!win.IsWindowClosed())
	{		
		loopman.BeginLoop();
		SPWindow::ProcessMessages();
		renderer->StartRendering();
		renderer->ClearBackBuffer(&color);		
		//renderer->GetCamera()->Walk(0.2f);


		rp.rotation.y += 0.003f;
		rp.Transform();
		teapot->Render(&rp);

		spotLight->heart.Position.y -=0.05f;
		spotLight->Register();

		renderer->StopRendering();
		loopman.EndLoop();
	}
	Pei::SPResourceManager::RemoveResources(0);
	return 0;
}