
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdateMailRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "ObjectMailPutMailByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPutMailByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectMailPutMailByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make ObjectMailPutMailByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAcceptAttachments,_Body,_Expires,_Subject,_State,_Category,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPutMailByObjectIdRequest* Make(int64 _ObjectId, int64 _MailId, FOptionalBool _bAcceptAttachments, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, FOptionalString _Category, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailByObjectIdSuccess, FBeamRequestContext, Context, UObjectMailPutMailByObjectIdRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailByObjectIdError, FBeamRequestContext, Context, UObjectMailPutMailByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPutMailByObjectIdComplete, FBeamRequestContext, Context, UObjectMailPutMailByObjectIdRequest*, Request);

using FObjectMailPutMailByObjectIdFullResponse = FBeamFullResponse<UObjectMailPutMailByObjectIdRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPutMailByObjectIdFullResponse, FObjectMailPutMailByObjectIdFullResponse);
