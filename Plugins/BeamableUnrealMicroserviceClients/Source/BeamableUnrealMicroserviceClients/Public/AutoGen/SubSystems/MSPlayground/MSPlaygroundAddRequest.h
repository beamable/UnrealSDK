
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AddRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundAddResponse.h"

#include "MSPlaygroundAddRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMSPlaygroundAddRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAddRequestArgs* Body = {};

	// Beam Base Request Declaration
	UMSPlaygroundAddRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MSPlaygroundAdd",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UMSPlaygroundAddRequest* Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundAddSuccess, FBeamRequestContext, Context, UMSPlaygroundAddRequest*, Request, UMSPlaygroundAddResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundAddError, FBeamRequestContext, Context, UMSPlaygroundAddRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMSPlaygroundAddComplete, FBeamRequestContext, Context, UMSPlaygroundAddRequest*, Request);

using FMSPlaygroundAddFullResponse = FBeamFullResponse<UMSPlaygroundAddRequest*, UMSPlaygroundAddResponse*>;
DECLARE_DELEGATE_OneParam(FOnMSPlaygroundAddFullResponse, FMSPlaygroundAddFullResponse);
