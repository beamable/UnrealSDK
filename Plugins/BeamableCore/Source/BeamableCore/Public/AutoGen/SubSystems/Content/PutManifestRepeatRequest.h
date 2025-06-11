
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutManifestRepeatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutManifestRepeatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URepeatManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutManifestRepeatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PutManifestRepeat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutManifestRepeatRequest* Make(FString _Uid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutManifestRepeatSuccess, FBeamRequestContext, Context, UPutManifestRepeatRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutManifestRepeatError, FBeamRequestContext, Context, UPutManifestRepeatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutManifestRepeatComplete, FBeamRequestContext, Context, UPutManifestRepeatRequest*, Request);

using FPutManifestRepeatFullResponse = FBeamFullResponse<UPutManifestRepeatRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutManifestRepeatFullResponse, FPutManifestRepeatFullResponse);
