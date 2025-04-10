
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SaveSKUsRequestBody.h"
#include "BeamableCore/Public/AutoGen/ResultResponse.h"

#include "PostSkusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSkusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USaveSKUsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSkusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PostSkus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSkusRequest* Make(TArray<USKU*> _Definitions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSkusSuccess, FBeamRequestContext, Context, UPostSkusRequest*, Request, UResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSkusError, FBeamRequestContext, Context, UPostSkusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSkusComplete, FBeamRequestContext, Context, UPostSkusRequest*, Request);

using FPostSkusFullResponse = FBeamFullResponse<UPostSkusRequest*, UResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSkusFullResponse, FPostSkusFullResponse);
