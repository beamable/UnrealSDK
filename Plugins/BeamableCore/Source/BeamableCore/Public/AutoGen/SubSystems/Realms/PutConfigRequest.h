
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RealmConfigSaveRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URealmConfigSaveRequestBody* Body;

	// Beam Base Request Declaration
	UPutConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutConfigRequest* MakePutConfigRequest(TMap<FString, FString> _Config, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutConfigSuccess, FBeamRequestContext, Context, UPutConfigRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutConfigError, FBeamRequestContext, Context, UPutConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutConfigComplete, FBeamRequestContext, Context, UPutConfigRequest*, Request);

using FPutConfigFullResponse = FBeamFullResponse<UPutConfigRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutConfigFullResponse, FPutConfigFullResponse);