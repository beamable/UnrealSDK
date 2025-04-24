
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UpdateMailRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "BasicMailPutMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicMailPutMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateMailRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicMailPutMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make BasicMailPutMail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAcceptAttachments,_Body,_Expires,_Subject,_State,_Category,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicMailPutMailRequest* Make(int64 _MailId, FOptionalBool _bAcceptAttachments, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, FOptionalString _Category, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailPutMailSuccess, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailPutMailError, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicMailPutMailComplete, FBeamRequestContext, Context, UBasicMailPutMailRequest*, Request);

using FBasicMailPutMailFullResponse = FBeamFullResponse<UBasicMailPutMailRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicMailPutMailFullResponse, FBasicMailPutMailFullResponse);
