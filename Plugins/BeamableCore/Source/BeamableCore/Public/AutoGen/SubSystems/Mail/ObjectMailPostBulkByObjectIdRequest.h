
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BulkSendMailRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "ObjectMailPostBulkByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPostBulkByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBulkSendMailRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectMailPostBulkByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make ObjectMailPostBulkByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPostBulkByObjectIdRequest* Make(int64 _ObjectId, TArray<USendMailRequestBody*> _SendMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkByObjectIdSuccess, FBeamRequestContext, Context, UObjectMailPostBulkByObjectIdRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkByObjectIdError, FBeamRequestContext, Context, UObjectMailPostBulkByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPostBulkByObjectIdComplete, FBeamRequestContext, Context, UObjectMailPostBulkByObjectIdRequest*, Request);

using FObjectMailPostBulkByObjectIdFullResponse = FBeamFullResponse<UObjectMailPostBulkByObjectIdRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPostBulkByObjectIdFullResponse, FObjectMailPostBulkByObjectIdFullResponse);
