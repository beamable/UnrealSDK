
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestArrRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundTestArrResponse.h"

#include "MSPlaygroundTestArrRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMSPlaygroundTestArrRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTestArrRequestArgs* Body = {};

	// Beam Base Request Declaration
	UMSPlaygroundTestArrRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MSPlaygroundTestArr",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UMSPlaygroundTestArrRequest* Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundTestArrSuccess, FBeamRequestContext, Context, UMSPlaygroundTestArrRequest*, Request, UMSPlaygroundTestArrResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundTestArrError, FBeamRequestContext, Context, UMSPlaygroundTestArrRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMSPlaygroundTestArrComplete, FBeamRequestContext, Context, UMSPlaygroundTestArrRequest*, Request);

using FMSPlaygroundTestArrFullResponse = FBeamFullResponse<UMSPlaygroundTestArrRequest*, UMSPlaygroundTestArrResponse*>;
DECLARE_DELEGATE_OneParam(FOnMSPlaygroundTestArrFullResponse, FMSPlaygroundTestArrFullResponse);
