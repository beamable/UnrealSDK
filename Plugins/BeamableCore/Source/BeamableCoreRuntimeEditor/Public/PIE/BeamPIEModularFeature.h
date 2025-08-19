#pragma once

#include "BeamCoreSettings.h"
#include "BeamLogging.h"
#include "IPIEAuthorizer.h"
#include "PIE/BeamPIEConfig.h"
#include "PIE/BeamPIE_Settings.h"
#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"


class UBeamPIEModularFeature : public IPIEAuthorizer
{
public:
	virtual bool RequestPIEPermission(bool bIsSimulateInEditor, FString& OutReason) const override
	{
		auto BeamCoreSettings = GetDefault<UBeamCoreSettings>();
		if (!BeamCoreSettings->bEnableBeamPIE) return true;

		auto PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

		int NumOfPlayers;
		PlaySettings->GetPlayNumberOfClients(NumOfPlayers);

		auto BeamPIEConfig = GetMutableDefault<UBeamPIEConfig>();

		FGuid SelectedSettingGUID;
		SelectedSettingGUID.Invalidate();

		auto Contexts = GEngine->GetWorldContexts();
		for (auto Context : Contexts)
		{
			UE_LOG(LogBeamEditor, Verbose, TEXT("GetWorldContexts %s"), *Context.World()->GetMapName());
		}

		if (Contexts.Num() == 0)
		{
			OutReason = TEXT("There's no level opened, you shouldn't be able to enter PIE mode.");
			return false;
		}

		const auto& World = Contexts[0].World();
		const auto& CurrentLevel = World->GetMapName();
		if (BeamPIEConfig->PerMapSelection.Contains(CurrentLevel))
		{
			SelectedSettingGUID = BeamPIEConfig->PerMapSelection[CurrentLevel];
		}
		UE_LOG(LogTemp, Display, TEXT("Current Level: %s"), *CurrentLevel);

		if (!SelectedSettingGUID.IsValid())
		{
			// If the selected settings is not valid that means there's no select settings for this level
			// So we just allow you to continue.
			return true;
		}

		FBeamPIE_Settings SelectedSetting;

		for (auto Setting : BeamPIEConfig->AllSettings)
		{
			if (Setting.SettingsId == SelectedSettingGUID)
			{
				SelectedSetting = Setting;
				break;
			}
		}
		FString ErrorReason = TEXT("");

		// Checking if the number of assigned user is the same as the play mode setup
		ErrorReason += NumOfPlayers != SelectedSetting.AssignedUsers.Num()
			               ? FString::Printf(
				               TEXT("\nThe number of players in the PIE Settings should be the same as in the Play config. [PIE Settings Players: %d] [Play Config Players: %d]"), SelectedSetting.AssignedUsers.Num(),
				               NumOfPlayers)
			               : TEXT("");

		auto DeveloperUserSubsystem = GEditor->GetEditorSubsystem<UBeamUserDeveloperManagerEditor>();
	
		// Checking the gamer tag for each assigned user
		for (auto AssignedUser : SelectedSetting.AssignedUsers)
		{
			ErrorReason += !DeveloperUserSubsystem->IsValidUser(AssignedUser.Value.GamerTag)
				               ? FString::Printf(TEXT("\nThe [PIE Index: %d UserSlot %s] is not configured correctly, it's missing the gamer tag."), AssignedUser.Key.PIEIndex, *AssignedUser.Key.Slot.Name)
				               : TEXT("");
		}

		EPlayNetMode PlayNetMode;
		PlaySettings->GetPlayNetMode(PlayNetMode);
		
		if (SelectedSetting.FakeLobby.bShouldAutoCreateLobby && PlayNetMode != PIE_Client)
		{
			ErrorReason += FString::Printf(TEXT("\nThe PIE config is not correct, you not able to have a \"Fake Lobby Settings\" enabled and start the game in a different settings than the \"Play As Client\""));
		}

		if (!ErrorReason.IsEmpty())
		{
			OutReason = FString::Printf(TEXT("BeamPIE Setting Failed: %s"), *ErrorReason);
			FMessageDialog WarningDialog;
			WarningDialog.Open(EAppMsgCategory::Error, EAppMsgType::Ok, FText::FromString(ErrorReason),FText::FromString(TEXT("BeamPIE Setting Failed")) );
			return false; // PIE will be blocked
		}

		return true; // Allow PIE
	}
};
