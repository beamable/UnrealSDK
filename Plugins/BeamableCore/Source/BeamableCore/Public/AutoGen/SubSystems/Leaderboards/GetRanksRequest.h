
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderBoardViewResponse.h"

#include "GetRanksRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRanksRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ids")
	FString Ids;

	// Body Params
	

	// Beam Base Request Declaration
	UGetRanksRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRanksRequest* MakeGetRanksRequest(FString _ObjectId, FString _Ids, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRanksSuccess, FBeamRequestContext, Context, UGetRanksRequest*, Request, ULeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRanksError, FBeamRequestContext, Context, UGetRanksRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRanksComplete, FBeamRequestContext, Context, UGetRanksRequest*, Request);

using FGetRanksFullResponse = FBeamFullResponse<UGetRanksRequest*, ULeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRanksFullResponse, FGetRanksFullResponse);
