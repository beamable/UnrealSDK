
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateProjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateProjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostProject",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bSharded,_Plan,_Parent,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostProjectRequest* Make(FString _Name, FOptionalBool _bSharded, FOptionalString _Plan, FOptionalString _Parent, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectSuccess, FBeamRequestContext, Context, UPostProjectRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectError, FBeamRequestContext, Context, UPostProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectComplete, FBeamRequestContext, Context, UPostProjectRequest*, Request);

using FPostProjectFullResponse = FBeamFullResponse<UPostProjectRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectFullResponse, FPostProjectFullResponse);
