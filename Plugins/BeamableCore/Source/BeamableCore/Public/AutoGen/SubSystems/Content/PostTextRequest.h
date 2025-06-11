
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SaveTextRequestBody.h"
#include "BeamableCore/Public/AutoGen/SaveTextResponse.h"

#include "PostTextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTextRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USaveTextRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PostText",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTextRequest* Make(TArray<UTextDefinition*> _Text, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTextSuccess, FBeamRequestContext, Context, UPostTextRequest*, Request, USaveTextResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTextError, FBeamRequestContext, Context, UPostTextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTextComplete, FBeamRequestContext, Context, UPostTextRequest*, Request);

using FPostTextFullResponse = FBeamFullResponse<UPostTextRequest*, USaveTextResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTextFullResponse, FPostTextFullResponse);
