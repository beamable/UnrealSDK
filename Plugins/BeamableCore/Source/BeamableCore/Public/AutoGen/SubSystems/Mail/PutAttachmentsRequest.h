
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AcceptMultipleAttachments.h"
#include "AutoGen/MailSuccessResponse.h"

#include "PutAttachmentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAttachmentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAcceptMultipleAttachments* Body;

	// Beam Base Request Declaration
	UPutAttachmentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutAttachmentsRequest* MakePutAttachmentsRequest(TArray<int64> _MailIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAttachmentsSuccess, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAttachmentsError, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAttachmentsComplete, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request);

using FPutAttachmentsFullResponse = FBeamFullResponse<UPutAttachmentsRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAttachmentsFullResponse, FPutAttachmentsFullResponse);