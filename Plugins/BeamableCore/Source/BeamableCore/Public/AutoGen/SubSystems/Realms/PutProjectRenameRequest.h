
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RenameProjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutProjectRenameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutProjectRenameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URenameProjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutProjectRenameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PutProjectRename",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutProjectRenameRequest* Make(FBeamPid _ProjectId, FString _NewName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectRenameSuccess, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectRenameError, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutProjectRenameComplete, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request);

using FPutProjectRenameFullResponse = FBeamFullResponse<UPutProjectRenameRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutProjectRenameFullResponse, FPutProjectRenameFullResponse);
