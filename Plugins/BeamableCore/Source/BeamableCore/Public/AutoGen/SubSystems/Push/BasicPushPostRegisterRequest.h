
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URegisterReq* Body;

	// Beam Base Request Declaration
	UBasicPushPostRegisterRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicPushPostRegisterRequest* MakeBasicPushPostRegisterRequest(FString _Provider, FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicPushPostRegisterSuccess, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request, UEmptyRsp*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicPushPostRegisterError, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicPushPostRegisterComplete, FBeamRequestContext, Context, UBasicPushPostRegisterRequest*, Request);

using FBasicPushPostRegisterFullResponse = FBeamFullResponse<UBasicPushPostRegisterRequest*, UEmptyRsp*>;
DECLARE_DELEGATE_OneParam(FOnBasicPushPostRegisterFullResponse, FBasicPushPostRegisterFullResponse);
