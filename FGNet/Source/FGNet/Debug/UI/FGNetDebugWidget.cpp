#include "FGNetDebugWidget.h"
#include "Engine/World.h"
#include "Engine/NetDriver.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Misc/DefaultValueHelper.h"

void UFGNetDebugWidget::UpdateNetworkSimulationSettings(const FFGBlueprintNetworkSimulationSettings& inPackets)
{
	if (UWorld* World = GetWorld())
	{
		if (World->GetNetDriver() != nullptr)
		{
			FPacketSimulationSettings PacketSimulation;
			PacketSimulation.PktLagMin = inPackets.MinLatency;
			PacketSimulation.PktLagMax = inPackets.MaxLatency;
			PacketSimulation.PktLoss = inPackets.PacketLossPercentage;
			PacketSimulation.PktIncomingLagMin = inPackets.MinLatency;
			PacketSimulation.PktIncomingLagMax = inPackets.MaxLatency;
			PacketSimulation.PktIncomingLoss = inPackets.PacketLossPercentage;
			World->GetNetDriver()->SetPacketSimulationSettings(PacketSimulation);

			FFGBlueprintNetworkSimulationSettingsText SimulationSettingsText;
			SimulationSettingsText.MaxLatency = FText::FromString(FString::FromInt(inPackets.MaxLatency));
			SimulationSettingsText.MinLatency = FText::FromString(FString::FromInt(inPackets.MinLatency));
			SimulationSettingsText.PacketLossPercentage = FText::FromString(FString::FromInt(inPackets.PacketLossPercentage));

			BP_OnUpdateNetworkSimulationSettings(SimulationSettingsText);
		}
	}
}

void UFGNetDebugWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APlayerState* PlayerState = PC->GetPlayerState<APlayerState>())
		{
			BP_UpdatePing(static_cast<int32>(PlayerState->GetPing()));
		}
	}
}