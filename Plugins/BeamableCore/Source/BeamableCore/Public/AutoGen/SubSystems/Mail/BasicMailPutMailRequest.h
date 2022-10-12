
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/UpdateMailRequestBody.h"
#include "AutoGen/MailSuccessResponse.h"

#include "BasicMailPutMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicMailPutMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UUpdateMailRequestBody* Body;

	// Beam Base Request Declaration
	UBasicMailPutMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Body,_Expires,_Subject,_State,_Category,_bAcceptAttachments,Outer"))
	static UBasicMailPutMailRequest* MakeBasicMailPutMailRequest(FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, int64 _MailId, FOptionalString _Category, FOptionalBool _bAcceptAttachments, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailPutMailSuccess, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailPutMailError, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicMailPutMailComplete, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request);

using FBasicMailPutMailFullResponse = FBeamFullResponse<UBasicMailPutMailRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicMailPutMailFullResponse, FBasicMailPutMailFullResponse);
