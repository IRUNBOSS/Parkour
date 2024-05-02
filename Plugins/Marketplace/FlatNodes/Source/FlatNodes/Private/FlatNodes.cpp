// Copyright 2023 Les Andro�ds Associ�s. All Rights Reserved.

#include "FlatNodes.h"
#include "FlatNodesSettings.h"
#include "Interfaces/IPluginManager.h"
#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleMacros.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FFlatNodesModule"

#define RootToContentDir Style->RootToContentDir


void FFlatNodesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (GIsEditor && !IsRunningCommandlet())
	{
		ApplyEditorStyle();
	}
}

void FFlatNodesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FFlatNodesModule::ApplyEditorStyle()
{
	FSlateStyleSet* Style = (FSlateStyleSet*)&FAppStyle::Get();
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("FlatNodes")->GetBaseDir() / TEXT("Resources"));

	UFlatNodesSettings* FlatNodesSettings = GetMutableDefault<UFlatNodesSettings>();
	const bool bHeaderUseGradient = FlatNodesSettings->bHeaderUseGradient;

	Style->Set("Graph.PlayInEditor", new BOX_BRUSH("Graph/RegularNode_shadow_selected", FMargin(18.0f / 64.0f)));

	Style->Set("Graph.Node.Body", new BOX_BRUSH("Graph/RegularNode_body", FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
	Style->Set("Graph.Node.TintedBody", new BOX_BRUSH("Graph/TintedNode_body", FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
	Style->Set("Graph.Node.TitleGloss", new BOX_BRUSH("Graph/RegularNode_title_gloss", FMargin(12.0f / 64.0f)));
	if (bHeaderUseGradient)
	{
		Style->Set("Graph.Node.ColorSpill", new BOX_BRUSH("Graph/RegularNode_color_spill", FMargin(8.0f / 64.0f, 3.0f / 32.0f, 0, 0)));
	}
	else
	{
		FSlateBrush* HeaderBrush = FlatNodesSettings->CreateHeaderBrush();
		HeaderBrush->Margin = FMargin(0, -1.0f / 32.0f, -3.0f / 20.0f, 0);
		HeaderBrush->DrawAs = ESlateBrushDrawType::Box;
		Style->Set("Graph.Node.ColorSpill", HeaderBrush);
	}
	Style->Set("Graph.Node.TitleHighlight", new BOX_BRUSH("Graph/RegularNode_title_highlight", FMargin(16.0f / 64.0f, 1.0f, 16.0f / 64.0f, 0.0f)));

	Style->Set("Graph.Node.ShadowSize", FVector2D(12, 12));
	Style->Set("Graph.Node.ShadowSelected", new BOX_BRUSH("Graph/RegularNode_shadow_selected", FMargin(18.0f / 64.0f)));
	Style->Set("Graph.Node.Shadow", new BOX_BRUSH("Graph/RegularNode_shadow", FMargin(18.0f / 64.0f)));

	Style->Set("Graph.VarNode.Body", new BOX_BRUSH("Graph/VarNode_body", FMargin(16.f / 64.f, 12.f / 28.f)));
	Style->Set("Graph.VarNode.ColorSpill", new IMAGE_BRUSH("Graph/VarNode_color_spill", FVector2D(132, 28)));
	Style->Set("Graph.VarNode.Gloss", new BOX_BRUSH("Graph/VarNode_gloss", FMargin(16.f / 64.f, 16.f / 28.f, 16.f / 64.f, 4.f / 28.f)));

	Style->Set("Graph.VarNode.ShadowSelected", new BOX_BRUSH("Graph/VarNode_shadow_selected", FMargin(26.0f / 64.0f)));
	Style->Set("Graph.VarNode.Shadow", new BOX_BRUSH("Graph/VarNode_shadow", FMargin(26.0f / 64.0f)));

	Style->Set("Graph.CollapsedNode.Body", new BOX_BRUSH("Graph/RegularNode_body", FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
	Style->Set("Graph.CollapsedNode.BodyColorSpill", new BOX_BRUSH("Graph/CollapsedNode_Body_ColorSpill", FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));

	Style->Set("Graph.ExecPin.Connected", new IMAGE_BRUSH("Old/Graph/ExecPin_Connected", FVector2D(12.0f, 16.0f)));
	Style->Set("Graph.ExecPin.Disconnected", new IMAGE_BRUSH("Old/Graph/ExecPin_Disconnected", FVector2D(12.0f, 16.0f)));
	Style->Set("Graph.ExecPin.ConnectedHovered", new IMAGE_BRUSH("Old/Graph/ExecPin_Connected", FVector2D(12.0f, 16.0f), FLinearColor(0.8f, 0.8f, 0.8f)));
	Style->Set("Graph.ExecPin.DisconnectedHovered", new IMAGE_BRUSH("Old/Graph/ExecPin_Disconnected", FVector2D(12.0f, 16.0f), FLinearColor(0.8f, 0.8f, 0.8f)));

	Style->Set("KismetExpression.ReadVariable.Body", new BOX_BRUSH("/Graph/Linear_VarNode_Background", FMargin(16.f / 64.f, 12.f / 28.f)));
	//Style->Set("KismetExpression.ReadVariable.Gloss", new BOX_BRUSH("/Graph/Linear_VarNode_Gloss", FMargin(16.f / 64.f, 12.f / 28.f)));
	Style->Set("KismetExpression.ReadAutogeneratedVariable.Body", new BOX_BRUSH("/Graph/Linear_VarNode_Background", FMargin(16.f / 64.f, 12.f / 28.f)));

	Style->Set("PhysicsAssetEditor.Graph.Node.Shadow", new BOX_BRUSH("Graph/RegularNode_shadow", FMargin(18.0f / 64.0f)));

	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFlatNodesModule, FlatNodes)