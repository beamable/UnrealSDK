
#include "BeamableCore/Public/AutoGen/LeaderboardDetailsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardDetailsLibrary::LeaderboardDetailsToJsonString(const ULeaderboardDetails* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

ULeaderboardDetails* ULeaderboardDetailsLibrary::Make(FString Lbid, int32 NumberOfEntries, FString FullName, ULeaderBoardView* View, FOptionalOrderRules Orules, FOptionalMetadataView MetaData, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardDetails>(Outer);
	Serializable->Lbid = Lbid;
	Serializable->NumberOfEntries = NumberOfEntries;
	Serializable->FullName = FullName;
	Serializable->View = View;
	Serializable->Orules = Orules;
	Serializable->MetaData = MetaData;
	
	return Serializable;
}

void ULeaderboardDetailsLibrary::Break(const ULeaderboardDetails* Serializable, FString& Lbid, int32& NumberOfEntries, FString& FullName, ULeaderBoardView*& View, FOptionalOrderRules& Orules, FOptionalMetadataView& MetaData)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Lbid = Serializable->Lbid;
		NumberOfEntries = Serializable->NumberOfEntries;
		FullName = Serializable->FullName;
		View = Serializable->View;
		Orules = Serializable->Orules;
		MetaData = Serializable->MetaData;
	}
		
}

