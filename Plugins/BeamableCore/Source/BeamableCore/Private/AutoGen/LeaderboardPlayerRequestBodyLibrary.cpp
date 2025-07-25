
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardPlayerRequestBodyLibrary::LeaderboardPlayerRequestBodyToJsonString(const ULeaderboardPlayerRequestBody* Serializable, const bool Pretty)
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

ULeaderboardPlayerRequestBody* ULeaderboardPlayerRequestBodyLibrary::Make(int64 Dbid, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardPlayerRequestBody>(Outer);
	Serializable->Dbid = Dbid;
	
	return Serializable;
}

void ULeaderboardPlayerRequestBodyLibrary::Break(const ULeaderboardPlayerRequestBody* Serializable, int64& Dbid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Dbid = Serializable->Dbid;
	}
		
}

