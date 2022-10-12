
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EventPhaseEndRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutEndPhaseRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutEndPhaseRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UEventPhaseEndRequestBody* Body;

	// Beam Base Request Declaration
	UPutEndPhaseRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Time,Outer"))
	static UPutEndPhaseRequest* MakePutEndPhaseRequest(int64 _ObjectId, FOptionalString _Time, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEndPhaseSuccess, FBeamRequestContext, Context, UPutEndPhaseRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutEndPhaseError, FBeamRequestContext, Context, UPutEndPhaseRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutEndPhaseComplete, FBeamRequestContext, Context, UPutEndPhaseRequest*, Request);

using FPutEndPhaseFullResponse = FBeamFullResponse<UPutEndPhaseRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutEndPhaseFullResponse, FPutEndPhaseFullResponse);
