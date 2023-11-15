
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnreal\AutoGen/MSPlaygroundAddRequestArgs.h"
#include "BeamableUnreal\AutoGen/MSPlaygroundMsAddResponse.h"

#include "MSPlaygroundMsAddRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREAL_API UMSPlaygroundMsAddRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMSPlaygroundAddRequestArgs* Body = {};

	// Beam Base Request Declaration
	UMSPlaygroundMsAddRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|MSPlaygroundMs", DisplayName="Beam - Make MSPlaygroundMsAdd",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UMSPlaygroundMsAddRequest* Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundMsAddSuccess, FBeamRequestContext, Context, UMSPlaygroundMsAddRequest*, Request, UMSPlaygroundMsAddResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundMsAddError, FBeamRequestContext, Context, UMSPlaygroundMsAddRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMSPlaygroundMsAddComplete, FBeamRequestContext, Context, UMSPlaygroundMsAddRequest*, Request);

using FMSPlaygroundMsAddFullResponse = FBeamFullResponse<UMSPlaygroundMsAddRequest*, UMSPlaygroundMsAddResponse*>;
DECLARE_DELEGATE_OneParam(FOnMSPlaygroundMsAddFullResponse, FMSPlaygroundMsAddFullResponse);
