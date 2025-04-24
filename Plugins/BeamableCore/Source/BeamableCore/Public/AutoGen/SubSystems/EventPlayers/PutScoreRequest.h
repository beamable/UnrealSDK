
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EventScoreRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutScoreRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutScoreRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEventScoreRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutScoreRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make PutScore",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIncrement,_Stats,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutScoreRequest* Make(int64 _ObjectId, FString _EventId, double _Score, FOptionalBool _bIncrement, FOptionalMapOfString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutScoreSuccess, FBeamRequestContext, Context, UPutScoreRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutScoreError, FBeamRequestContext, Context, UPutScoreRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutScoreComplete, FBeamRequestContext, Context, UPutScoreRequest*, Request);

using FPutScoreFullResponse = FBeamFullResponse<UPutScoreRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutScoreFullResponse, FPutScoreFullResponse);
