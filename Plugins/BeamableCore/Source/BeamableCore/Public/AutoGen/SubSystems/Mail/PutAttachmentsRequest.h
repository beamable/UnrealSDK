
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AcceptMultipleAttachments.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "PutAttachmentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAttachmentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAcceptMultipleAttachments* Body = {};

	// Beam Base Request Declaration
	UPutAttachmentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make PutAttachments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAttachmentsRequest* Make(TArray<int64> _MailIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAttachmentsSuccess, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAttachmentsError, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAttachmentsComplete, FBeamRequestContext, Context, UPutAttachmentsRequest*, Request);

using FPutAttachmentsFullResponse = FBeamFullResponse<UPutAttachmentsRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAttachmentsFullResponse, FPutAttachmentsFullResponse);
