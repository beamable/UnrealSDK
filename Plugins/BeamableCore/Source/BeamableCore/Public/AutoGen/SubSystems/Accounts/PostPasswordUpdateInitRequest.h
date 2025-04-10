
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PasswordUpdateRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostPasswordUpdateInitRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPasswordUpdateInitRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPasswordUpdateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostPasswordUpdateInitRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PostPasswordUpdateInit",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_CodeType,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPasswordUpdateInitRequest* Make(FString _Email, FOptionalString _CodeType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateInitSuccess, FBeamRequestContext, Context, UPostPasswordUpdateInitRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateInitError, FBeamRequestContext, Context, UPostPasswordUpdateInitRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPasswordUpdateInitComplete, FBeamRequestContext, Context, UPostPasswordUpdateInitRequest*, Request);

using FPostPasswordUpdateInitFullResponse = FBeamFullResponse<UPostPasswordUpdateInitRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPasswordUpdateInitFullResponse, FPostPasswordUpdateInitFullResponse);
