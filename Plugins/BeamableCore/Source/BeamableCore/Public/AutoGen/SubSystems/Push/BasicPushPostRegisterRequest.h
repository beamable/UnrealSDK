
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/RegisterReq.h"
#include "AutoGen/EmptyRsp.h"

#include "BasicPushPostRegisterRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicPushPostRegisterRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URegisterReq* Body;

	// Beam Base Request Declaration
	UBasicPushPostRegisterRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Push", DisplayName="Beam - Make BasicPushPostRegister",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicPushPostRegisterRequest* Make(FString _Provider, FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicPushPostRegisterSuccess, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request, UEmptyRsp*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicPushPostRegisterError, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicPushPostRegisterComplete, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request);

using FBasicPushPostRegisterFullResponse = FBeamFullResponse<UBasicPushPostRegisterRequest*, UEmptyRsp*>;
DECLARE_DELEGATE_OneParam(FOnBasicPushPostRegisterFullResponse, FBasicPushPostRegisterFullResponse);
