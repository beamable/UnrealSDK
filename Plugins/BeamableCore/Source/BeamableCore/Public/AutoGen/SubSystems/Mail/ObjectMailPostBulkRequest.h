
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/BulkSendMailRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "ObjectMailPostBulkRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPostBulkRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectMailPostBulkRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Mail", DisplayName="Beam - Make ObjectMailPostBulk",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPostBulkRequest* Make(int64 _ObjectId, TArray<USendMailRequestBody*> _SendMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkSuccess, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkError, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPostBulkComplete, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request);

using FObjectMailPostBulkFullResponse = FBeamFullResponse<UObjectMailPostBulkRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPostBulkFullResponse, FObjectMailPostBulkFullResponse);
