
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAddRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutEntryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutEntryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaderboardAddRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutEntryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make PutEntry",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIncrement,_MaxScore,_MinScore,_Stats,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutEntryRequest* Make(FString _ObjectId, double _Score, int64 _Id, FOptionalBool _bIncrement, FOptionalDouble _MaxScore, FOptionalDouble _MinScore, FOptionalMapOfString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEntrySuccess, FBeamRequestContext, Context, UPutEntryRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEntryError, FBeamRequestContext, Context, UPutEntryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutEntryComplete, FBeamRequestContext, Context, UPutEntryRequest*, Request);

using FPutEntryFullResponse = FBeamFullResponse<UPutEntryRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutEntryFullResponse, FPutEntryFullResponse);
