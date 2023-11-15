
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/UpdateMailRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "ObjectMailPutMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPutMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateMailRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectMailPutMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Mail", DisplayName="Beam - Make ObjectMailPutMail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAcceptAttachments,_Body,_Expires,_Subject,_State,_Category,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPutMailRequest* Make(int64 _ObjectId, int64 _MailId, FOptionalBool _bAcceptAttachments, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, FOptionalString _Category, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailSuccess, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailError, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPutMailComplete, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request);

using FObjectMailPutMailFullResponse = FBeamFullResponse<UObjectMailPutMailRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPutMailFullResponse, FObjectMailPutMailFullResponse);
