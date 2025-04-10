
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#include "GetRanksRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRanksRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ids", Category="Beam")
	FString Ids = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetRanksRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make GetRanks",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRanksRequest* Make(FString _ObjectId, FString _Ids, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRanksSuccess, FBeamRequestContext, Context, UGetRanksRequest*, Request, ULeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRanksError, FBeamRequestContext, Context, UGetRanksRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRanksComplete, FBeamRequestContext, Context, UGetRanksRequest*, Request);

using FGetRanksFullResponse = FBeamFullResponse<UGetRanksRequest*, ULeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRanksFullResponse, FGetRanksFullResponse);
