
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderboardAddRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutEntryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutEntryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	ULeaderboardAddRequestBody* Body;

	// Beam Base Request Declaration
	UPutEntryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_MaxScore,_Stats,_MinScore,_bIncrement,Outer"))
	static UPutEntryRequest* MakePutEntryRequest(FString _ObjectId, FOptionalDouble _MaxScore, FOptionalMapOfString _Stats, double _Score, FOptionalDouble _MinScore, int64 _Id, FOptionalBool _bIncrement, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEntrySuccess, FBeamRequestContext, Context, UPutEntryRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEntryError, FBeamRequestContext, Context, UPutEntryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutEntryComplete, FBeamRequestContext, Context, UPutEntryRequest*, Request);

using FPutEntryFullResponse = FBeamFullResponse<UPutEntryRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutEntryFullResponse, FPutEntryFullResponse);
